# image ubuntu pour la base
FROM ubuntu:latest 

# installation
RUN apt-get update && \
    apt-get install -y openssh-server && \
    apt-get install -y git && \
    apt-get install -y curl

# creation d'un nouveau user
RUN useradd -ms /bin/bash git_user

# demande la generation des cles car sinon le conteneur ne se lance pas.
RUN ssh-keygen -A

# dossier de separation de privileges necessaire pour sshd
RUN mkdir -p /run/sshd

# ajout de la cle publique de jenkins dans les cles autorisees du serv git pour que jenkins puisse se connecter sans etre bloque
# creation du dossier
RUN mkdir -p /home/git_user/.ssh && \
    chmod 700 /home/git_user/.ssh && \
    chown git_user:git_user /home/git_user/.ssh
# copie de la cle du fichier au conteneur
COPY ssh_key.pub /home/git_user/.ssh/authorized_keys

# seul le user git_user a le droit d'ecrire et lire car le fichier est sensible (cles ssh autorisees a se connecter)
RUN chmod 600 /home/git_user/.ssh/authorized_keys && \
    chown git_user:git_user /home/git_user/.ssh/authorized_keys

# on passe sur git_user et on initialise le depot avec branche main
USER git_user
RUN git init --bare -b main /home/git_user/repos/monprojet.git

# on ajoute le hook post-receive en faisant attention aux permissions
COPY --chown=git_user:git_user post-receive.sh /home/git_user/repos/monprojet.git/hooks/post-receive
RUN chmod +x /home/git_user/repos/monprojet.git/hooks/post-receive

# passage en user root pour lancer le ssh
USER root

# on expose le port 22 pour n'avoir que le ssh de dispo (important pour qu'on puisse pousser du code dessus)
EXPOSE 22

# allumage du serv ssh
CMD ["/usr/sbin/sshd", "-D"]
