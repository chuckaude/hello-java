pipeline {
	agent any

	jdk = tool name: 'openjdk-11'
	env.JAVA_HOME = "${jdk}"

	environment {
		CONNECT = 'http://coverity.chuckaude.com:8080/'
		PROJECT = 'hello-java'
		STREAM = "$PROJECT-$BRANCH_NAME"
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
				withCoverityEnvironment(coverityInstanceUrl: "$CONNECT", projectName: "$PROJECT", streamName: "$STREAM") {
					sh '''
						env | sort
						cov-build --dir $IDIR --fs-capture-search $WORKSPACE mvn -B package -DskipTests
						cov-analyze --dir $IDIR --ticker-mode none --strip-path $WORKSPACE --webapp-security
						cov-commit-defects --dir $IDIR --ticker-mode none --url $COV_URL --stream $COV_STREAM --description $BUILD_TAG --target Linux_x86_64 --version $GIT_COMMIT
					'''
				}
			}
		}
		stage('Coverity Incremental Scan') {
			when {
				changeRequest()
			}
			steps {
				sh 'env | sort'
				echo 'Coverity INCR scan'
			}
		}
		stage('Deploy') {
			when {
				anyOf {
					branch 'release-*'
				}
			}
			steps {
				sh 'mvn -B install'
			}
		}
	}
}
