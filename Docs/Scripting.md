# **R-Type Scripting Level Guide**
---------------------
>Les levels du R-Type seront totalement scripté dans un fichier.<br>
Ce fichier devra respecter une certaine syntaxe qui est détaillée plus tard. <br>Des levels ont déjà été codés si vous voulez regarder.

### __Sommaire__
##### Nom du script
* _Syntaxe_:
        name "{stage_name}"
* _Usage_:
        name "stage_dark_vador"

##### Liste des ressources nécessaires
* _Syntaxe_:
        require "{ressource_name}"
* _Usage_:
        require "{ship}"
        require "{boss_dark_vador}"

##### Liste des actions
* _Syntaxe_:
        action {frame} {spawnMobAt(id_monster, name, x, y, angle)}
        action {frame} {moveMobTo(id_monster, new_angle)}
        add_cron {frame} {timer} {id_cron} {fireMob(id_monster, angle)}
        remove_cron {frame} {id_cron}
* _Usage_:
        action 42 spawnMobAt(1, monster_basic, 380, 40, 230)
        action 42 spawnMobAt(2, monster_basic, 380, 250, 270)
        action 42 spawnMobAt(3, monster_basic, 380, 480, 310)
        add_cron 42 10 1 fireMob(1, 270)
        add_cron 42 10 2 fireMob(2, 270)
        add_cron 42 10 3 fireMob(3, 270)
        remove_cron 2500 1
        remove_cron 2500 2
        remove_cron 2500 3
        action 125 moveMobTo(1, 310)

