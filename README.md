# hello-java

A simple hello world Java app with some errors for testing with Coverity and Polaris

Build on CLI
- mvn clean package (pom.xml)
- ant clean build (build.xml)
- gradle clean assemble (build.gradle)

Build with CI
- ado-build.yml - normal build (Maven) on Azure DevOps
- ado-coverity.yml - Coverity BAC (Maven) on Azure DevOps
- Jenkinsfile.coverity - Coverity BAC (Maven) on Jenkins
- Jenkinsfile.polaris - Polaris (Maven) on Jenkins
- polaris.yml - Polaris project configuration (Gradle)
- .gitlab-ci.yml - GitLab CI pipeline (Gradle)
