# WSL pour faire tourner un Linux ultra léger sous Windows

Sous windows, Window Subsystem est comme une machine virtuelle en bien plus léger (ne prend pas de partition supplémentaire, ne demande pas de double boot, etc.).

* [Installation de WSL-Ubuntu depuis le store Windows](https://docs.microsoft.com/en-us/windows/wsl/install-win10)
* [Une autre explication de l'installation](https://korben.info/installer-wsl2-windows-linux.html)
* Si vous êtes avec Windows 10 il faut installer [XMing qui est un serveur X pour windows pour pouvoir ouvrir des fenêtres depuis votre WSL-Ubuntu](https://sourceforge.net/projects/xming/)
* Sous Windows 11, pas besoin de d'installer un serveur X en plus, il est intégré.
* Puis faire les installations comme sous linux (vous êtes sous Linux) avec apt install
* Lancer XMing



## WSL version 1 (préférer vraiment la version 2)

* Depuis le terminal Ubuntu, faire `export DISPLAY=":0.0"`
* Tester avec xclock. Il faut l'avoir installé avec `sudo apt install x11-apps`
* Pour ne pas refaire ca à chaque fois, il faut définir l'écran local comme l'écran du "display" en ajoutant la ligne `export     DISPLAY=":0.0` dans votre fichier .profile ou .bashrc. Lancez Ubuntu puis le fichier .bashrc doit être là dans `${HOME}`


## WSL version 2

* Avec WSL2, en cas de problème d'autorisation d'ouverture de fenêtre, il y a plus de choses à faire 
  * [voir la page de LIFASR5 (notamment pour le pare-feu)](https://nlouvet.gitlabpages.inria.fr/lifasr5/wsl.html)
  * mettre les deux variables DISPLAY et LIBGL_ALWAYS_INDIRECT dans ~/.bashc ⇒ pour SDL parfois il faut mettre LIBGL_ALWAYS_INDIRECT à 0 contrairement à ce qu'indique nombre de sites web.

```
  export DISPLAY=$(grep -m 1 nameserver /etc/resolv.conf | awk '{print $2}'):0
  export LIBGL_ALWAYS_INDIRECT=0
```

## En cas de problème

* **Problème d'autorisation: can't display :0.0** Si vous avez des problèmes de connexion d'authentification essayer aussi de décocher `disable access control` en lançant le programme `C:\\Program Files (x86)\\Xming\\Xlaunch.exe`. C'est à la dernière question. Puis relancez XMing.
* Regardez le fichier de log de XMing : depuis l'icône de XMing en bas dans la barre, bouton droit, View Log. Si dans ces log vous voyez que XMing a refusé une connexion, alors essayer de basculer à "disable access control" de la ligne ci-dessus. Dans le fichier `C:\\Program Files (x86)\\Xming\\X0.hosts` ajouter les lignes avec l'adresse IP qui a été refusée dans les logs. Par exemple `172.19.199.187`
* Il faudra potentiellement refaire ca à chaque reboot (car l'adresse IP de la distribution change). Je cherche pour automatiser ceci ...
* Si le fichier de log reste vide, c'est que la demande d'ouverture de fenêtre a été bloquée avant par le pare-feu
* [La doc de Xming](http://www.straightrunning.com/XmingNotes/#head-144)


#### Les commandes WSL dans un power shell

```
wsl --set-default-version 2               # définir la version 2 par défaut pour la prochaine installation
wsl -l -v                                 # afficher les versions
wsl --list --verbose                      # afficher les versions
wsl --set-version <votre ditribution> 2   # Convertir la distribution <votre distribution> en version 2
```
