pipeline {
    agent { 
        node {
            label 'docker-agent-alpine'
            }
      }
    stages {
        stage('Build') {
            steps {
                echo "Building.."
                sh '''
                echo "doing build stuff.."
                '''
            }
        }
        stage('Test') {
            steps {
                echo "Testing.."
                sh '''
                echo "doing test stuff.."
                '''
            }
        }
        stage('pre-analysis SCM') {
            steps {
                checkout scm
            }
        }
        stage('SonarQube Analysis') {
            steps {
                def scannerHome = tool name: 'SonarScanner'
                withSonarQubeEnv('Sonar-Server') {
                    sh "${scannerHome}/bin/sonar-scanner"
                }
            }     
        }
        stage('Deliver') {
            steps {
                echo 'Deliver....'
                sh '''
                echo "doing delivery stuff.."
                '''
            }
        }
    }
}
