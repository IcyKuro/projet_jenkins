FROM jenkins/jenkins:lts

USER root
RUN apt-get update && apt-get install -y build-essential valgrind && rm -rf /var/lib/apt/lists/*

USER jenkins
