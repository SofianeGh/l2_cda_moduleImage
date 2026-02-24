# Présentation rapide de CodeBlocks

CodeBlocks est plus qu'un éditeur de code. C'est un "environnement de développement intégré" (IDE en anglais). CodeBlocks va gérer votre
programme comme un projet. Vous pourrez par exemple déboguer directement dans l'éditeur.

Remarque : codeblocks est un peu vieillissant. Il reste relativement plus simple d'utilisation que Visual Studio ou d'autres plus. Si vous ne connaissez pas codeblocks, essayez peut-être d'abord [Visual Code et ses extensions](vscode) ou [Visual Studio](./visualstudio.md) si vous êtes sous Windows. Si vous êtes sous Mac, regardez [XCode](./xcode.md).

## Pour créer, compiler et exécuter un projet sous CodeBlocks

* `cd LIFAP_TD`
* Lancer codeblocks
* Cliquez sur "Create a new project", sélectionnez "Empty project"
* Project title=''LIFAP_TD'' et Folder=''/home/.../'' (le chemin vers le répertoire du projet)
* Une fois votre projet crée, cliquez avec le bouton droit sur "LIFAP_TD" à gauche puis sur "Add file" et choisissez 'main.cpp' ou bien "New file" et donner lui le nom de 'main.cpp' si vous n'avez pas déjà de fichier principal.
* Explorez le menu "Build" (Alt-b) pour apprendre les raccourcis clavier 
  * **F9** pour "Compile & Run" (le plus important)
  * **Ctrl-F9** pour "Compile"
  * **Ctrl-F10** pour "Run"
  * **Alt-F2** pour aller à une erreur (si Alt-F2 est pris par le système, sinon allez dans "Settings/editor/shortcut" pour configurer vos raccourcis clavier).
  * **Ctrl-espace** pour compléter un nom de fonction ou un nom de variable (essayez en tapant 'pr' 'Ctrl-espace' pour voir apparaître ''printf'').
  * **Shift-Ctrl-x**, **Shift-Ctrl-c** pour dé/commenter du code
  * **Ctrl-Tab**, **Ctrl-Shift-Tab** pour naviguer dans les onglets

Voir également [ce tutoriel](http://loulou.developpez.com/tutoriels/cpp/codeblocks/) si besoin.
