# mod-all-professions-npc

`mod-all-professions-npc` adds a **Profession Master** NPC to AzerothCore. The NPC presents a gossip menu that teaches the apprentice spell for every WotLK primary and secondary profession:

- Alchemy, Blacksmithing, Enchanting, Engineering, Herbalism, Inscription, Jewelcrafting, Leatherworking, Mining, Skinning, and Tailoring
- Cooking, First Aid, and Fishing

Primary-profession limits are respected. The module uses AzerothCore's normal free-primary-profession check, so the limit follows `MaxPrimaryTradeSkill` in `worldserver.conf`. Secondary professions do not consume a primary profession slot.

## Requirements

- An AzerothCore WotLK checkout.
- MySQL or MariaDB access to the realm's **world** database.
- Permission to rebuild and restart `worldserver`.

## Installation

From the root of your AzerothCore checkout:

```bash
git clone https://github.com/rfahey79/mod-all-professions-npc.git modules/mod-all-professions-npc
./acore.sh compiler build
```

Import the two SQL files into the realm's **world** database, in this order:

```bash
mysql <world_database> < modules/mod-all-professions-npc/data/sql/db-world/profession_master.sql
mysql <world_database> < modules/mod-all-professions-npc/data/sql/db-world/profession_master_spawns.sql
```

Restart `worldserver` after the build and SQL import.

## What the SQL installs

The SQL creates the Profession Master creature template with entry **190011**, assigns it the script name `npc_all_professions_trainer`, and adds eight default world spawns. The spawn file is optional if you prefer to place the NPC yourself.

To add your own spawn instead, import only `profession_master.sql`, then use a GM command such as:

```text
.npc add 190011
```

## Usage

Talk to a Profession Master and choose the profession from its gossip menu. The NPC teaches the base apprentice-level spell only; players still advance their skill and learn further ranks/recipes through the usual game systems.

If a player already knows a profession, the NPC leaves it unchanged. If the player has no free primary-profession slots, the NPC shows a message and does not teach another primary profession.

## Configuration

There is no module-specific configuration file. To change the number of primary professions a player may have, use AzerothCore's standard worldserver option:

```ini
MaxPrimaryTradeSkill = 2
```

Set it to the desired number and restart `worldserver`. The Profession Master automatically follows that setting.
