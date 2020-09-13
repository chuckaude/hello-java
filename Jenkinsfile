pipeline {
	agent any

	stages {
		stage('Build') {
			steps {
				sh 'env | sort'
				echo 'Building...'
			}
		}
		stage('Test') {
			steps {
				echo 'Testing...'
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
				echo 'Coverity FULL scan'
			}
		}
		stage('Coverity Incremental Scan') {
			when {
				changeRequest()
			}
			steps {
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
				echo 'Deploying...'
			}
		}
	}
}
