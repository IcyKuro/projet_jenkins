FROM jenkins/jenkins:lts

USER root
# build-essential : gcc, make, strip ; valgrind : profilage ; file : inspection du binaire avant et apres strip
RUN apt-get update && apt-get install -y build-essential valgrind file && rm -rf /var/lib/apt/lists/* \
    && mkdir -p /opt/tri_bulles && chown jenkins:jenkins /opt/tri_bulles

USER jenkins
RUN jenkins-plugin-cli --plugins workflow-aggregator git github
