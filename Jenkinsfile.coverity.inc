pipeline {

	agent any

	environment {
		CONNECT = 'http://sal-moonhyun-vm01.dc1.lan:8080'
		PROJECT = 'hello-java-coverity-demo'
		STREAM = "$PROJECT-jenkins"
	}
	
	stages {
		stage('Coverity Incremental Scan') {
			steps {
				withCoverityEnvironment(coverityInstanceUrl: "$CONNECT", projectName: "$PROJECT", streamName: "$STREAM") {
					sh '''
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
