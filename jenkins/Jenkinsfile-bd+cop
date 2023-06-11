// Example Jenkinsfile with SIG Security Scan that implements:
// - Black Duck INTELLIGENT scan on pushes and RAPID scan on PRs to "important" branches
// - Coverity on Polaris FULL scan on pushes and PRs to "important" branches
pipeline {
    agent { label 'linux64' }
    environment {
        // production branches on which we want security reports
        PRODUCTION = "${env.BRANCH_NAME ==~ /^(stage|release)$/ ? 'true' : 'false'}"
        // full scan on pushes to important branches
        FULLSCAN = "${env.BRANCH_NAME ==~ /^(main|master|develop|stage|release)$/ ? 'true' : 'false'}"
        // PR scan on pulll requests to important branches
        PRSCAN = "${env.CHANGE_TARGET ==~ /^(main|master|develop|stage|release)$/ ? 'true' : 'false'}"
        // set project name to be repo name
        PROJECT = sh(script: "basename $GIT_URL .git", returnStdout: true).trim()
        // Bridge CLI download URL
        BRIDGECLI_LINUX64 = 'https://sig-repo.synopsys.com/artifactory/bds-integrations-release/com/synopsys/integration/synopsys-bridge/latest/synopsys-bridge-linux64.zip'
    }
    tools {
        maven 'maven-3.9'
        jdk 'openjdk-17'
    }
    stages {
        stage('Build') {
            steps {
                sh 'mvn -B compile'
            }
        }
        stage('Test') {
            steps {
                sh 'mvn -B test'
            }
        }
        stage('Scan') {
            parallel {
                stage('Black Duck Full Scan') {
                    when { environment name: 'FULLSCAN', value: 'true' }
                    environment {
                        DETECT_PROJECT_NAME = "$PROJECT"
                        DETECT_PROJECT_VERSION_NAME = "$BRANCH_NAME"
                        DETECT_CODE_LOCATION_NAME = "$PROJECT-$BRANCH_NAME"
                        DETECT_RISK_REPORT_PDF = "${env.PRODUCTION == 'true' ? 'true' : 'false'}"
                        DETECT_EXCLUDED_DETECTOR_TYPES = 'GIT'
                    }
                    steps {
                        withCredentials([string(credentialsId: 'testing.blackduck.synopsys.com', variable: 'BRIDGE_BLACKDUCK_TOKEN')]) {
                            script {
                                status = sh returnStatus: true, script: """
                                    curl -fLsS -o bridge.zip $BRIDGECLI_LINUX64 && unzip -qo -d $WORKSPACE_TMP bridge.zip && rm -f bridge.zip
                                    $WORKSPACE_TMP/synopsys-bridge --verbose --stage blackduck \
                                        blackduck.url=$BLACKDUCK_URL \
                                        blackduck.scan.failure.severities='BLOCKER' \
                                        blackduck.scan.full='true'
                                """
                                if (status == 8) { unstable 'policy violation' }
                                else if (status != 0) { error 'scan failure' }
                            }
                        }
                    }
                }
                stage('Black Duck PR Scan') {
                    // Bridge CLI PR comments currently not supported from Jenkins - see INTEGRATE-23
                    when { environment name: 'PRSCAN', value: 'true' }
                    environment {
                        DETECT_PROJECT_NAME = "$PROJECT"
                        DETECT_PROJECT_VERSION_NAME = "$CHANGE_TARGET"
                        DETECT_CODE_LOCATION_NAME = "$PROJECT-$CHANGE_TARGET"
                        DETECT_EXCLUDED_DETECTOR_TYPES = 'GIT'
                        BRIDGE_ENVIRONMENT_SCAN_PULL = 'true'
                    }
                    steps {
                        withCredentials([string(credentialsId: 'testing.blackduck.synopsys.com', variable: 'BRIDGE_BLACKDUCK_TOKEN'),
                                         string(credentialsId: 'github-pat', variable: 'GITHUB_TOKEN')]) {
                            script {
                                status = sh returnStatus: true, script: """
                                    curl -fLsS -o bridge.zip $BRIDGECLI_LINUX64 && unzip -qo -d $WORKSPACE_TMP bridge.zip && rm -f bridge.zip
                                    $WORKSPACE_TMP/synopsys-bridge --verbose --stage blackduck \
                                        blackduck.url=$BLACKDUCK_URL \
                                        blackduck.scan.full='false' \
                                        blackduck.automation.prcomment='true' \
                                        github.repository.branch.name=$BRANCH_NAME \
                                        github.repository.name=$PROJECT \
                                        github.repository.owner.name=$CHANGE_AUTHOR \
                                        github.repository.pull.number=$CHANGE_ID \
                                        github.user.token=$GITHUB_TOKEN
                                """
                                if (status == 8) { unstable 'policy violation' }
                                else if (status != 0) { error 'scan failure' }
                            }
                        }
                    }
                }
                stage('Coverity on Polaris Full Scan') {
                    when { environment name: 'FULLSCAN', value: 'true' }
                    steps {
                        withCredentials([string(credentialsId: 'sipse.polaris.synopsys.com', variable: 'POLARIS_ACCESS_TOKEN')]) {
                            script {
                                status = sh returnStatus: true, script: """
                                    curl -fLOsS $POLARIS_SERVER_URL/api/tools/polaris_cli-linux64.zip
                                    unzip -qo -d $WORKSPACE_TMP -jo polaris_cli-linux64.zip && rm -f polaris_cli-linux64.zip
                                    $WORKSPACE_TMP/polaris --co project.name=$PROJECT analyze -w
                                    # simple quality gate for critical and high impact issues; more advanced filtering requires an API script
                                    if [ \$(cat .synopsys/polaris/cli-scan.json | jq '[.issueSummary.issuesBySeverity|.critical,.high]|add') -ne 0 ]; then exit 8; fi
                                """
                                if (status == 8) { unstable 'policy violation' }
                                else if (status != 0) { error 'scan failure' }
                            }
                        }
                    }
                }
                stage('Coverity on Polaris PR Scan') {
                    when { environment name: 'PRSCAN', value: 'true' }
                    steps {
                        withCredentials([string(credentialsId: 'sipse.polaris.synopsys.com', variable: 'POLARIS_ACCESS_TOKEN')]) {
                            script {
                                status = sh returnStatus: true, script: """
                                    curl -fLOsS $POLARIS_SERVER_URL/api/tools/polaris_cli-linux64.zip
                                    unzip -qo -d $WORKSPACE_TMP -jo polaris_cli-linux64.zip && rm -f polaris_cli-linux64.zip
                                    $WORKSPACE_TMP/polaris --co project.name=$PROJECT analyze -w
                                    # query for new issues; will always be non-zero for PRs; replace with API script to compare with CHANGE_TARGET
                                    if [ \$(cat .synopsys/polaris/cli-scan.json | jq '.issueSummary.newIssues') -ne 0 ]; then exit 8; fi
                                """
                                if (status == 8) { unstable 'policy violation' }
                                else if (status != 0) { error 'scan failure' }
                            }
                        }
                    }
                }
            }
        }
        stage('Deploy') {
            when { environment name: 'PRODUCTION', value: 'true' }
            steps {
                sh 'mvn -B -DskipTests install'
            }
        }
    }
    post {
        always {
            archiveArtifacts allowEmptyArchive: true, artifacts: '.synopsys/polaris/configuration/synopsys.yml, .synopsys/polaris/data/coverity/*/idir/build-log.txt, *_BlackDuck_RiskReport.pdf'
            //zip archive: true, dir: '.bridge', zipFile: 'bridge-logs.zip'
            cleanWs()
        }
    }
}
