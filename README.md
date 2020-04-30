# hello-java

A simple hello world Java app with some coding errors for testing with Coverity and Polaris

Build on CLI
- mvn clean package i[pom.xml](pom.xml)
- ant clean build [build.xml](build.xml)
- gradle clean assemble [build.gradle](build.gradle)

Build with CI
- [ado-build.yml](ado-build.yml) - normal build (Maven) on Azure DevOps
- [ado-coverity.yml](ado-coverity.yml) - Coverity (Maven) on Azure DevOps
- [ado-polaris.yml](ado-polaris.yml) - Polaris (Maven) on Azure DevOps
- [Jenkinsfile.coverity](Jenkinsfile.coverity) - Coverity (Maven) on Jenkins
- [Jenkinsfile.polaris](Jenkinsfile.polaris) - Polaris (Maven) on Jenkins
- [polaris.yml](polaris.yml) - Polaris project configuration (Maven)
- [.gitlab-ci.yml](.gitlab-ci.yml) - GitLab CI pipeline (Maven)
- [.circleci/config.yml](.circleci/config.yml) - Circle CI pipeline (Maven)
