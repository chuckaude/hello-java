pipeline {
	agent any

	tools {
		jdk 'openjdk-11'
	}

	environment {
		CONNECT = 'http://coverity.chuckaude.com:8080/'
		PROJECT = 'hello-java'
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
		stage('Coverity Full Scan') {
			when {
				anyOf {
					branch 'master'
					branch 'release-*'
				}
			}
			steps {
				withCoverityEnvironment(coverityInstanceUrl: "$CONNECT", projectName: "$PROJECT", streamName: "$PROJECT-$BRANCH_NAME") {
					sh '''
						env | sort
						cov-build --dir idir --fs-capture-search $WORKSPACE mvn -B clean compile
						cov-analyze --dir idir --ticker-mode none --strip-path $WORKSPACE --webapp-security
						cov-commit-defects --dir idir --ticker-mode none --url $COV_URL --stream $COV_STREAM --description $BUILD_TAG --target Linux_x86_64 --version $GIT_COMMIT
					'''
				}
			}
		}
		stage('Coverity Incremental Scan') {
			when {
				changeRequest()
			}
			steps {
				withCoverityEnvironment(coverityInstanceUrl: "$CONNECT", projectName: "$PROJECT", streamName: "$PROJECT-$CHANGE_TARGET") {
					sh '''
						env | sort
						CHANGE_SET=$(git --no-pager diff origin/$CHANGE_TARGET --name-only)
						cov-build --dir idir --fs-capture-search $WORKSPACE mvn -B clean compile
						cov-run-desktop --dir idir --url $COV_URL --stream $COV_STREAM --ignore-uncapturable-inputs true --reference-snapshot latest --present-in-reference false --exit1-if-defects true $CHANGE_SET
					'''
				}
			}
		}
		stage('Deploy') {
			when {
				anyOf {
					branch 'release-*'
				}
			}
			steps {
				sh 'mvn -B install -DskipTests'
			}
		}
	}
}
