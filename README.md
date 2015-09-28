# Zappy
Adaptation &amp; creativity, Group &amp; interpersonal, Organization, Unix

note finale :
103 / 100

Zappy est un jeu entièrement automatique où des programmes informatiques jouent
entre eux. Le jeu se déroule selon une vitesse définie par une unité de temps. Chaque
action dans le jeu prend une durée proportionnelle à cette unité de temps.

L’unité de temps est définie par la fonction 1/t :
• t est passé en paramètre au démarrage du serveur,
• une unité de temps dure 1/t secondes
Voici les différentes parties constituant ce jeu :
• un serveur qui contient le terrain, les ressources, et gère la logique et le timing du
jeu.
• un ou plusieurs clients qui se connectent au serveur et “pilotent” chacun un joueur.
Les joueurs sont répartit en équipe.
• un client graphique qui se connecte au serveur et affiche le terrain et ce qu’il s’y
passe.

Le jeu consiste à gérer un monde et ses habitants. Ce monde, nommé Trantor est
géographiquement constitué de plaines ne comprenant aucun relief : ni cratère, ni vallée,
ni montagne. Le plateau de jeu représente la totalité de la surface de ce monde comme
un planisphère. Si un joueur sort par la droite du plateau, il rentrera par la gauche.
Le jeu se joue par équipe. L’équipe gagnante est celle dont six joueurs auront atteint
l’élévation maximale.

Le milieu dans lequel on évolue est plutôt riche en ressources, tant minières qu’alimentaires.
Ainsi, il suffit de déambuler sur cette planète pour découvrir cette succulente
nourriture ou une multitude de pierres de diverses natures.
Ces pierres sont de six genres distincts. Il existe la linemate, la deraumère, le sibur, la
mendiane, le phiras, la thystame. La génération des ressources est réalisé par le serveur.
Cette génération doit être aléatoire et comprenant des règles de logique.

Les habitants de Trantor vaquent à deux types d’occupation :
• récupérer de la nourriture pour se nourrir et ne pas mourrir de faim,
• rechercher et amasser des pierres pour fabriquer des totems, procéder à un rituel
d’élévation et passer au niveau supérieur.
L’élévation représente une activité importante du Trantorien.

L’habitant est pacifique. Il n’est ni violent ni agressif.
Il déambule gaiement en quête de pierres et s’alimente au passage.
Il croise sans difficulté ses congénaires sur la même unité de terrain et voit aussi loin
que ses capacités visuelles le lui permettent.
Le Trantorien est immatériel, il est flou et occupe toute la case dans laquel il se trouve.
Il est impossible de distinguer son orientation lorsqu’on le croise.
La nourriture que le trantorien ramasse est la seul ressource dont il a besoin pour vivre.
Une unité de nourriture permet de survivre 126 unité de temps, donc 126/t secondes.

L’objectif de tous est de s’élever dans la hiérarchie Trantorienne. Ce rituel qui permet
d’accroître ses capacités physiques et mentales doit être effectué selon un rite particulier.
Il faut en effet réunir sur la même unité de terrain :
• une combinaison de pierres,
• un certain nombre de joueurs de même niveau.
Un joueur débute l’incantation et l’élévation est alors en cours. Il n’est pas nécessaire
que les joueurs soient de la même équipe. Seul leur niveau importe. Tous les joueurs du
groupe réalisant l’incantation atteignent le niveau supérieur.

Pour diverses raisons, le champ de vision des joueurs est limité. A chaque élévation,
la vision augmente d’une unité de mesure en avant et d’une de chaque côté de la nouvelle
rangée.

Pour que le joueur ait connaissance de son entourage, le client envoie la commande
’VOIR’, et le serveur répond la chaîne de caractères suivante (schéma pour un niveau 1) :
{contenu-case-0, contenu-case-1, contenu-case-2, contenu-case-3}

Le son est une onde qui se propage de manière linéaire.
Tout les joueurs entendent les broadcasts sans savoir qui les émet. Ils percoivent uniquement
la direction d’où provient le son et le message émis. La direction est indiquée
par le numéro de la case franchie par le son avant d’arriver dans la case du joueur. Cette
numérotation est effectuée par l’attribution du ‘1’ à la case devant le joueur, puis à un
décomptage des cases entourant le joueur dans le sens trigonométrique (anti-horaire). Le
monde étant sphérique le trajet que l’on choisira pour le son sera le plus court chemin
reliant l’émetteur au joueur pour lequel on le calcule.

Un serveur réalisé en C sur le dump de l’école aura comme tâche de gérer le monde
et ses habitants.
Le serveur s’exécute sous la forme d’un seul process et un seul thread (ce qui veut
dire : PAS DE THREAD !)

Un client réalisé en C, en PHP, en Perl, en pyhton, etc... (tant que ça fonctionne sur
les dumps), pilotera un habitant par des ordres qu’il enverra au serveur.
Le client est autonome, après son lancement l’utilisateur n’influe plus sur son fonctionnement.
Il pilote un drone (joueur) comme dans le projet corewar.

Au commencement une équipe est composée de n joueurs et seulement n. Chaque
joueur est piloté par un client. Les clients ne peuvent pas communiquer ou échanger
entre eux des données en dehors du jeu, de quelque façon que ce soit.
Au début le client possède 10 unité de vie, il peut donc survivre 1260 unités de temps,
soit 1260/t secondes.

Le dialogue entre le client et le serveur s’effectuera via sockets et tcp. Le port utilisé
sera indiqué en paramètre des programmes.
Le client envoie ses requêtes sans attendre leur réalisation, le serveur renvoie un message
confirmant le bon déroulement de l’exécution des requêtes.

Le nb-client indique le nombre de clients pouvant encore être acceptés par le serveur
pour l’équipe nom-equipe.
Si ce nombre est supérieur à 1 un nouveau client se connecte.
Le serveur exécute les requêtes des clients dans l’ordre de réception. Les requêtes sont
bufferisées et le délai d’exécution d’une commande ne bloque que le joueur concerné.
x et y indiquent les dimensions du monde.

Les Trantoriens ont adoptés une unité de temps internationale. L’unité de temps est
la seconde. Si t = 1, ’avance’ prend 7 secondes. On choisira par défaut, t = 100. t est un
entier.
Le référentiel de temps est le temps absolu.

Seul la classe des objets est identifiable. Il est ainsi impossible de distinguer deux objets
de la même classe. Par exemple, deux siburs auront la même dénomination puisqu’ils
appartiennent à la même classe.

Un joueur peut se reproduire grâce à la commande fork. L’exécution de cette commande
entraîne la production d’un oeuf. Dès la ponte le joueur l’ayant pondu peut vaquer
à ses occupations en attendant qu’il éclose. Lors de l’éclosion de l’oeuf, un nouveau joueur
en sort, il est orienté au hasard. Cette opération autorise la connection d’un nouveau
client. La commande connect_nbr renvoie le nombre de connections autorisées et non
autorisées pour cette famille.
Délai de ponte : 42/t.
Délai entre la ponte et l’éclosion : 600/t.

Cette commandes permet de voir ce que le drone a comme objet et combien de temps
il lui reste a vivre. Le seveur enverra par exemple la ligne suivante :
{nourriture 345, sibur 3, phiras 5, ..., deraumere 0}

Pour émettre un message, le client doit envoyer au serveur la commande suivante :
broadcast <texte>
Le serveur, lui, enverra à tous les clients la ligne suivante :
message <K>,<texte>
avec K indiquant la case d’où provient le son.

Le drone à la faculté d’expulser tous les drones partageant la même unité de terrain. Il
les pousse dans la direction qu’il regarde. Lorsqu’un client envoie au serveur la commande
expulse, tous les clients partageant cette case recoivent la ligne suivante :
deplacement <K>\n
avec K indiquant la direction de la case d’où le drone provient.

Le projet devra être muni d’un client de visualisation graphique. Celui-ci devra proposer
une représentation en temps réel du monde tel qu’il est sur le serveur.
L’interface doit intégrer au minimum une visualisation 2D par l’intermédiaire d’icônes,
permettant ainsi une représentation du monde. L’interface 3-D ou tout autre type de représentation
sera un atout appréciable au projet. Il faut de plus inclure la visualisation
des sons.
Il sera réalisé en C, en PHP, en Perl, en pyhton, etc... (tant que ça fonctionne sur
les dumps), et communiquera en réseau avec le serveur pour récupérer le contenu de la
map, des équipes, des inventaires, etc... bref tout ce qu’il faut pour pouvoir voir ce qu’il
se passe dans le jeu.
