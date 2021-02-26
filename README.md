# hello-java

A simple hello world Java app with some coding errors for demoing Coverity and Polaris integration with various CI systems.

Build Commands
- [pom.xml](pom.xml) - mvn clean compile
- [build.xml](build.xml) - ant clean build
- [build.gradle](build.gradle) - gradle clean assemble

CI Integration Examples (Maven)
- [.circleci/config.yml](.circleci/config.yml) - Circle CI pipeline
- [.github/workflows/coverity-private.yml](.github/workflows/coverity-private.yml) - GitHub Workflow for Coverity on self-hosted runner
- [.github/workflows/coverity-public.yml](.github/workflows/coverity-public.yml) - GitHub Workflow for Coverity on GitHub-hosted runner
- [.github/workflows/polaris-private.yml](.github/workflows/polaris-private.yml) - GitHub Workflow for Polaris on self-hosted runner
- [.github/workflows/polaris-public.yml](.github/workflows/polaris-public.yml) - GitHub Workflow for Polaris on GitHub-hosted runner
- [.gitlab-ci.yml](.gitlab-ci.yml) - GitLab CI pipeline
- [azure-pipelines/build.yml](azure-pipelines/build.yml) - normal build on Azure DevOps
- [azure-pipelines/onprem-coverity-gpr.yml](azure-pipelines/onprem-coverity-gpr.yml) - Coverity Git Pull Request scanning on Azure DevOps
- [azure-pipelines/onprem-coverity-noplugin.yml](azure-pipelines/onprem-coverity-noplugin.yml) - No-Plugin Coverity on Azure DevOps
- [azure-pipelines/onprem-coverity-plugin.yml](azure-pipelines/onprem-coverity-plugin.yml) - Coverity Plugin on Azure DevOps
- [azure-pipelines/polaris-noplugin.yml](azure-pipelines/polaris-noplugin.yml) - No-Plugin Polaris on Azure DevOps
- [azure-pipelines/polaris-plugin.yml](azure-pipelines/polaris-plugin.yml) - Polaris Plugin on Azure DevOps
- [bitbucket/coverity-pipeline.yml](bitbucket/coverity-pipeline.yml) - Coverity on Bitbucket pipeline
- [bitbucket/polaris-pipeline.yml](bitbucket/polaris-pipeline.yml) - Polaris on Bitbucket pipeline
- [Jenkinsfile](Jenkinsfile) - Coverity on Jenkins with full + incr scans using GitHub Branch Source plugin
- [Jenkinsfile.coverity](Jenkinsfile.coverity) - Coverity on Jenkins
- [Jenkinsfile.polaris](Jenkinsfile.polaris) - Polaris on Jenkins
- [polaris.yml](polaris.yml) - Polaris project configuration
