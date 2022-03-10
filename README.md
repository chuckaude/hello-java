# hello-java

A simple hello world Java app with some coding errors for demoing SIG product integrations with various CI systems.

Build Commands
- [pom.xml](pom.xml) - mvn clean compile
- [build.xml](build.xml) - ant clean build
- [build.gradle](build.gradle) - gradle clean assemble

CI Integration Examples (configured for Maven)
- [.circleci/config.yml](.circleci/config.yml) - Circle CI pipeline
- [.github/workflows](.github/workflows) - example GitHub workflows
- [.gitlab-ci.yml](.gitlab-ci.yml) - GitLab CI pipeline
- [azure-pipelines](azure-pipelines) - example Azure DevOps pipelines
- [bitbucket](bitbucket) - example Bitbucket pipelines
- [jenkins](jenkins) - example Jenkins pipelines
- [Jenkinsfile](Jenkinsfile) - Coverity on Jenkins with full + incr scans using GitHub Branch Source plugin
- [polaris.yml](polaris.yml) - Polaris project configuration
