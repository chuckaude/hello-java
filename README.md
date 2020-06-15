# hello-java

A simple hello world Java app with some coding errors for testing with Coverity and Polaris

Build Commands
- [pom.xml](pom.xml) - mvn clean compile
- [build.xml](build.xml) - ant clean build
- [build.gradle](build.gradle) - gradle clean assemble

CI Integration Examples (Maven)
- [ado-build.yml](ado-build.yml) - normal build on Azure DevOps
- [ado-coverity.yml](ado-coverity.yml) - Coverity on Azure DevOps
- [ado-polaris.yml](ado-polaris.yml) - Polaris on Azure DevOps
- [Jenkinsfile.coverity](Jenkinsfile.coverity) - Coverity on Jenkins
- [Jenkinsfile.polaris](Jenkinsfile.polaris) - Polaris on Jenkins
- [polaris.yml](polaris.yml) - Polaris project configuration
- [.circleci/config.yml](.circleci/config.yml) - Circle CI pipeline
- [.github/workflows/polaris-public.yml](.github/workflows/polaris-public.yml) - GitHub Workflow for Polaris
- [.gitlab-ci.yml](.gitlab-ci.yml) - GitLab CI pipeline
