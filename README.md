# hello-java

A simple hello world Java app with some coding errors for demoing SIG product integrations with various CI systems.

Build Commands
- [pom.xml](pom.xml) - mvn clean compile
- [build.xml](build.xml) - ant clean build
- [build.gradle](build.gradle) - gradle clean assemble

CI Integration Examples (configured for Maven)
- [.circleci/config.yml](.circleci/config.yml) - CircleCI pipeline examples
- [cloudbuild.yaml](cloudbuild.yaml) - Google Cloud Build pipeline examples
- [coverity.yaml](coverity.yaml) - Coverity CLI configuration file
- [.github/workflows](.github/workflows) - GitHub workflow examples
- [.gitlab-ci.yml](.gitlab-ci.yml) - GitLab CI pipeline examples
- [ado](ado) - Azure DevOps pipeline examples
- [bitbucket](bitbucket) - Bitbucket pipeline examples
- [jenkins](jenkins) - Jenkins pipeline examples
- [polaris.yml](polaris.yml) - Coverity on Polaris configuration file
