pipeline {
	agent any

	environment {
		CONNECT = 'http://sal-moonhyun-vm01.dc1.lan:8080'
		PROJECT = 'hello-java-coverity-demo'
	}
	
	stages {
		stage('Coverity Incremental Scan') {
			when {
				allOf {
				    expression { env.CHANGE_ID != null }
				    expression { env.CHANGE_TARGET != null }
				}
			}
			steps {
				withCoverityEnvironment(coverityInstanceUrl: "$CONNECT", projectName: "$PROJECT", streamName: "$PROJECT-$CHANGE_TARGET") {
					sh '''
						export CHANGE_SET=$(git --no-pager diff origin/$CHANGE_TARGET --name-only)
						[ -z "$CHANGE_SET" ] && exit 0
						cov-run-desktop --dir idir --url $COV_URL --stream $COV_STREAM --build mvn -B clean package -DskipTests
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
	post {
		always {
			cleanWs()
		}
	}
}
