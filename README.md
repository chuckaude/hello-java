# hello-java

A simple hello world Java app with some coding errors for testing with Coverity and Polaris

Build Commands
- [pom.xml](pom.xml) - mvn clean compile
- [build.xml](build.xml) - ant clean build
- [build.gradle](build.gradle) - gradle clean assemble

CI Integration Examples (Maven)
- [.circleci/config.yml](.circleci/config.yml) - Circle CI pipeline
- [.github/workflows/coverity-private.yml](.github/workflows/coverity-private.yml) - GitHub Workflow for Coverity on self-hosted runner
- [.github/workflows/polaris-public.yml](.github/workflows/polaris-public.yml) - GitHub Workflow for Polaris on GitHub-hosted runner
- [.github/workflows/polaris-private.yml](.github/workflows/polaris-private.yml) - GitHub Workflow for Polaris on self-hosted runner
- [.gitlab-ci.yml](.gitlab-ci.yml) - GitLab CI pipeline
- [azure-pipelines/build.yml](azure-pipelines/build.yml) - normal build on Azure DevOps
- [azure-pipelines/onprem-coverity-gpr.yml](azure-pipelines/onprem-coverity-gpr.yml) - Coverity Git Pull Request on Azure DevOps
- [azure-pipelines/onprem-coverity-noplugin.yml](azure-pipelines/onprem-coverity-noplugin.yml) - No-Plugin Coverity on Azure DevOps
- [azure-pipelines/onprem-coverity-plugin.yml](azure-pipelines/onprem-coverity-plugin.yml) - Coverity Plugin on Azure DevOps
- [azure-pipelines/polaris-noplugin.yml](azure-pipelines/polaris-noplugin.yml) - No-Plugin Polaris on Azure DevOps
- [azure-pipelines/polaris-plugin.yml](azure-pipelines/polaris-plugin.yml) - Polaris Plugin on Azure DevOps
- [Jenkinsfile](Jenkinsfile) - build-test-deploy on Jenkins
- [Jenkinsfile.coverity](Jenkinsfile.coverity) - Coverity on Jenkins
- [Jenkinsfile.polaris](Jenkinsfile.polaris) - Polaris on Jenkins
- [polaris.yml](polaris.yml) - Polaris project configuration
