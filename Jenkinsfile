node {
    def GIT_REPO = 'https://github.com/chuckaude/hello-java.git'
    def BRANCH = 'master'
    def CONNECT = 'localhost'
    def PROJECT = 'hello-java'
    def STREAM = 'hello-java'
    def IDIR = '${WORKSPACE}/idir'
 
    def COVBIN = '/opt/coverity/analysis/latest/bin'
 
    stage('clean') {
        deleteDir()
    }
    stage('checkout') {
        git url: "${GIT_REPO}", credentialsId: 'github-chuckaude', branch: "${BRANCH}"
        GIT_COMMIT = sh(returnStdout: true, script: 'git log -n 1 --pretty=format:%H').trim()
    }
    stage('build') {
        sh "${COVBIN}/cov-build --dir ${IDIR} --fs-capture-search ${WORKSPACE} mvn clean package -DskipTests"
    }
    stage('import-scm') {
        sh "${COVBIN}/cov-import-scm --dir ${IDIR} --scm git --filename-regex ${WORKSPACE}"
    }
    stage('analyze') {
        sh "${COVBIN}/cov-analyze --dir ${IDIR} --strip-path ${WORKSPACE} --all --enable-callgraph-metrics --webapp-security"
    }
    withCredentials([usernamePassword(credentialsId: 'coverity-committer', usernameVariable: 'COV_USER', passwordVariable: 'COVERITY_PASSPHRASE')]) {
        stage('commit') {
            sh "${COVBIN}/cov-commit-defects --dir ${IDIR} --host ${CONNECT} --stream ${STREAM} --description ${BUILD_TAG} --target Linux_x86_64 --version ${GIT_COMMIT}"
        }
        stage('results') {
            sh "curl -s --user ${COV_USER}:${COVERITY_PASSPHRASE} ${CONNECT}:8080/api/viewContents/issues/v1/Outstanding%20Issues?projectId=${PROJECT} | tee results.json | python -m json.tool"
        }
    }
}
