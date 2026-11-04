# Importer les jobs dans l'interface Jenkins

Ce guide explique comment créer les trois pipelines `tri-bulles-dev`, `tri-bulles-preprod` et `tri-bulles-prod` dans Jenkins à partir des Jenkinsfiles du dépôt GitHub. Il y a deux méthodes : par l'interface web, recommandée, ou par fichier de configuration XML.

## Prérequis

Docker Desktop doit être lancé, avec le moteur en état « Engine running ». Ensuite, depuis la racine du projet :

```powershell
docker compose up -d --build
docker exec jenkins-container cat /var/jenkins_home/secrets/initialAdminPassword
```

Ouvrir http://localhost:8080, coller le mot de passe affiché, choisir « Install suggested plugins », créer le compte admin, puis vérifier que le plugin GitHub apparaît dans Administrer Jenkins > Plugins > Installed plugins. S'il manque, l'installer en ligne de commande :

```powershell
docker exec jenkins-container jenkins-plugin-cli --plugin-download-directory /var/jenkins_home/plugins --plugins github
docker restart jenkins-container
```

## Méthode 1 : par l'interface web (recommandée)

1. Sur http://localhost:8080, cliquer sur « Nouveau Item » (« New Item »).
2. Saisir le nom `tri-bulles-dev`, choisir « Pipeline », puis valider avec OK. Le nom doit être exact, car les Jenkinsfiles s'enchaînent par leur nom.
3. Dans la page de configuration, descendre jusqu'à la section « Pipeline ».
4. Dans « Definition », choisir « Pipeline script from SCM ».
5. Dans « SCM », choisir « Git ».
6. Dans « Repository URL », mettre `https://github.com/IcyKuro/projet_jenkins.git`. Si le dépôt est privé, ajouter un credential dans « Credentials » : nom d'utilisateur GitHub et token personnel, jamais le mot de passe du compte.
7. Dans « Branch Specifier », mettre `*/main`.
8. Dans « Script Path », mettre `Jenkinsfile.dev`.
9. Laisser « Lightweight checkout » coché et cliquer sur « Sauvegarder ».
10. Recommencer les étapes 1 à 9 pour `tri-bulles-preprod` avec `Jenkinsfile.preprod`, puis pour `tri-bulles-prod` avec `Jenkinsfile.prod`.
11. Lancer une fois chaque job à la main avec « Lancer un build ».

La dernière étape est indispensable. Jenkins ne connaît les `triggers` d'un pipeline, comme le `pollSCM` qui surveille GitHub, qu'après avoir lu et exécuté son Jenkinsfile une première fois. Sans ce premier build, aucun déclenchement automatique ne se produit.

## Méthode 2 : par fichier de configuration

Un job Jenkins n'est qu'un dossier `/var/jenkins_home/jobs/<nom>/` qui contient un `config.xml`. Ce fichier décrit exactement ce que les étapes 4 à 9 de la méthode 1 remplissent dans l'interface. Cette méthode peut s'automatiser sans se connecter à l'interface. En contrepartie, rien ne valide le contenu du fichier : une erreur dans le XML ne se voit qu'au démarrage de Jenkins.

Voici le fichier du job dev. Pour preprod et prod, seuls `description` et `scriptPath` changent.

```xml
<?xml version='1.1' encoding='UTF-8'?>
<flow-definition plugin="workflow-job">
  <description>Pipeline dev du projet tri_bulles</description>
  <definition class="org.jenkinsci.plugins.workflow.cps.CpsScmFlowDefinition" plugin="workflow-cps">
    <scm class="hudson.plugins.git.GitSCM" plugin="git">
      <configVersion>2</configVersion>
      <userRemoteConfigs><hudson.plugins.git.UserRemoteConfig><url>https://github.com/IcyKuro/projet_jenkins.git</url></hudson.plugins.git.UserRemoteConfig></userRemoteConfigs>
      <branches><hudson.plugins.git.BranchSpec><name>*/main</name></hudson.plugins.git.BranchSpec></branches>
    </scm>
    <scriptPath>Jenkinsfile.dev</scriptPath>
    <lightweight>true</lightweight>
  </definition>
</flow-definition>
```

Enregistrer ce fichier sous `jobs\dev\config.xml`, puis le copier dans le conteneur depuis PowerShell :

```powershell
docker exec jenkins-container mkdir -p /var/jenkins_home/jobs/tri-bulles-dev
docker cp jobs\dev\config.xml jenkins-container:/var/jenkins_home/jobs/tri-bulles-dev/config.xml
docker restart jenkins-container
```

Faire de même pour `tri-bulles-preprod` et `tri-bulles-prod`. Le redémarrage est nécessaire parce que Jenkins ne relit le dossier `jobs` qu'au démarrage. On peut aussi passer par Administrer Jenkins > « Recharger la configuration depuis le disque ».

Avec Git Bash au lieu de PowerShell, il faut d'abord lancer `export MSYS_NO_PATHCONV=1`. Sinon, Git Bash convertit `/var/jenkins_home/...` en chemin Windows et les commandes `docker exec` et `docker cp` échouent.

Comme pour la méthode 1, chaque job doit ensuite être lancé une fois à la main pour activer son déclencheur.

## Vérification

Les trois jobs apparaissent sur le tableau de bord de http://localhost:8080. Après le premier build de `tri-bulles-dev`, la vue du build affiche les stages, les logs de compilation et de tests, et les fichiers archivés.
