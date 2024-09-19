// example Jenkinsfile for Polaris scans using the Synopsys Security Scan Plugin
// https://plugins.jenkins.io/synopsys-security-scan
pipeline {
    agent { label 'linux64' }
    environment {
        REPO_NAME = "${env.GIT_URL.tokenize('/.')[-2]}"
        FULLSCAN = "${env.BRANCH_NAME ==~ /^(main|master|develop|stage|release)$/ ? 'true' : 'false'}"
        PRSCAN = "${env.CHANGE_TARGET ==~ /^(main|master|develop|stage|release)$/ ? 'true' : 'false'}"
        BRIDGE_POLARIS_SERVERURL = 'https://poc.polaris.synopsys.com'
        BRIDGE_POLARIS_ACCESSTOKEN = credentials('poc.polaris.synopsys.com')
        //GITHUB_TOKEN = credentials('github-pat')
    }
    tools {
        maven 'maven-3.9'
        jdk 'openjdk-17'
    }
    stages {
        stage('Environment') {
            steps {
                sh 'env | sort'
            }
        }
        stage('Build') {
            steps {
                sh 'mvn -B package'
            }
        }
        stage('Polaris') {
            steps {
                synopsys_scan product: 'polaris',
                    polaris_assessment_types: 'SAST,SCA',
                    polaris_application_name: "chuckaude-$REPO_NAME",
                    polaris_project_name: "$REPO_NAME",
                    polaris_branch_name: "$BRANCH_NAME",
                    polaris_prComment_enabled: true,
                    polaris_reports_sarif_create: true,
                    mark_build_status: 'UNSTABLE'
                    //github_token: "$GITHUB_TOKEN"
            }
        }
    }
    post {
        always {
            archiveArtifacts allowEmptyArchive: true, artifacts: '.bridge/bridge.log, .bridge/*/idir/build-log.txt, .bridge/*/report.sarif.json'
            //zip archive: true, dir: '.bridge', zipFile: 'bridge-logs.zip'
            cleanWs()
        }
    }
}
