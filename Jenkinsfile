pipeline {
    agent { label 'linux64' }

    environment {
        CONNECT = 'https://coverity.chuckaude.com:8443'
        PROJECT = 'hello-java'
        BLDCMD = 'mvn -B package -DskipTests'
        CHECKERS = '--webapp-security --enable-callgraph-metrics'
        COVERITY_NO_LOG_ENVIRONMENT_VARIABLES = '1'
    }

    tools {
        maven 'maven-3.8'
        jdk 'openjdk-11'
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
        stage('Security Testing') {
            parallel {
                stage('Black Duck') {
                    steps {
                        synopsys_detect "--detect.project.name=$PROJECT --detect.project.version.name=$BRANCH_NAME"
                    }
                }
                stage('Coverity Full Scan') {
                    when {
                        allOf {
                            not { changeRequest() }
                            expression { BRANCH_NAME ==~ /(main|stage|release)/ }
                        }
                    }
                    steps {
                        withCoverityEnvironment(coverityInstanceUrl: "$CONNECT", projectName: "$PROJECT", streamName: "$PROJECT-$BRANCH_NAME") {
                            sh '''
                                cov-build --dir idir --fs-capture-search $WORKSPACE $BLDCMD
                                cov-analyze --dir idir --ticker-mode none --strip-path $WORKSPACE $CHECKERS
                                cov-commit-defects --dir idir --ticker-mode none --url $COV_URL --stream $COV_STREAM \
                                    --description $BUILD_TAG --version $GIT_COMMIT
                            '''
                            script { // Coverity Quality Gate
                                count = coverityIssueCheck(viewName: 'OWASP Web Top 10', returnIssueCount: true)
                                if (count != 0) { unstable 'issues detected' }
                            }
                        }
                    }
                }
                stage('Coverity Incremental Scan') {
                    when {
                        allOf {
                            changeRequest()
                            expression { CHANGE_TARGET ==~ /(main|stage|release)/ }
                        }
                    }
                    steps {
                        withCoverityEnvironment(coverityInstanceUrl: "$CONNECT", projectName: "$PROJECT", streamName: "$PROJECT-$CHANGE_TARGET") {
                            sh '''
                                export CHANGE_SET=$(git --no-pager diff origin/$CHANGE_TARGET --name-only)
                                [ -z "$CHANGE_SET" ] && exit 0
                                cov-run-desktop --dir idir --url $COV_URL --stream $COV_STREAM --build $BLDCMD
                                cov-run-desktop --dir idir --url $COV_URL --stream $COV_STREAM --present-in-reference false \
                                    --ignore-uncapturable-inputs true --text-output issues.txt $CHANGE_SET
                                if [ -s issues.txt ]; then cat issues.txt; touch issues_found; fi
                            '''
                        }
                        script { // Coverity Quality Gate
                            if (fileExists('issues_found')) { unstable 'issues detected' }
                        }
                    }
                }
            }
        }
        stage('Deploy') {
            when {
                expression { BRANCH_NAME ==~ /(main|stage|release)/ }
            }
            steps {
                sh 'mvn -B install'
            }
        }
    }
    post {
        always {
            archiveArtifacts artifacts: 'idir/build-log.txt, idir/output/analysis-log.txt, idir/output/callgraph-metrics.csv'
            cleanWs()
        }
    }
}
