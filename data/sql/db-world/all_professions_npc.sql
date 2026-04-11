-- Pick an unused creature_template entry ID
SET @ENTRY := 900001;

DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template`
(
    `entry`, `modelid1`, `name`, `subname`, `IconName`,
    `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`,
    `npcflag`, `speed_walk`, `speed_run`, `scale`,
    `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`,
    `RegenHealth`, `VerifiedBuild`, `ScriptName`
)
VALUES
(
    @ENTRY, 19723, 'Profession Master', 'Learn any profession', '',
    0, 80, 80, 35,
    1, 1, 1.14286, 1,
    0, 1, 0, 7, 0,
    1, 12340, 'npc_all_professions_trainer'
);
