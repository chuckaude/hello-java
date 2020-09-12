pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
		sh 'env | sort'
                sh 'mvn -B compile'
            }
        }
        stage('Test') {
            steps {
                sh 'mvn -B test'
            }
        }
        stage('Deploy') {
            steps {
                sh 'mvn -B install'
            }
        }
    }
}
