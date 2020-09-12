pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                mvn -B compile
            }
        }
        stage('Test') {
            steps {
                mvn -B test
            }
        }
        stage('Deploy') {
            steps {
                mvn -B install
            }
        }
    }
}
