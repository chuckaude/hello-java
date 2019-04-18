node {
	def GIT_REPO = 'https://github.com/chuckaude/hello-java.git'
	def BRANCH = 'master'
	def CONNECT = 'localhost'
	def PROJECT = 'hello-java'
	def STREAM = 'hello-java'
	def IDIR = '${WORKSPACE}/idir'

	stage('clean') {
		deleteDir()
	}
	stage('checkout') {
		git url: "${GIT_REPO}", branch: "${BRANCH}"
		GIT_COMMIT = sh(returnStdout: true, script: 'git log -n 1 --pretty=format:%H').trim()
	}
	withCoverityEnv(coverityToolName: 'latest', connectInstance: "${CONNECT}") { 
		stage('build') {
			sh "cov-build --dir ${IDIR} --fs-capture-search ${WORKSPACE} mvn -B clean package -DskipTests"
		}
		stage('import-scm') {
			sh "cov-import-scm --dir ${IDIR} --scm git --filename-regex ${WORKSPACE}"
		}
		stage('analyze') {
			sh "cov-analyze --dir ${IDIR} --strip-path ${WORKSPACE} --all --enable-callgraph-metrics --webapp-security"
		}
		stage('commit') {
			sh "cov-commit-defects --dir ${IDIR} --host ${COVERITY_HOST} --stream ${STREAM} --description ${BUILD_TAG} --target Linux_x86_64 --version ${GIT_COMMIT}'
		}
	}
	stage('results') {
		coverityResults connectInstance: "${CONNECT}", connectView: 'Outstanding Issues', projectId: "${PROJECT}", abortPipeline: false, failPipeline: false, unstable: false
	}
}
