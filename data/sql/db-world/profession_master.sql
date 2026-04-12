SET @ENTRY := 190011;
SET @NAME := 'Profession Master';
SET @DISPLAYID := 23405;

-- clean up any leftover gameobject version
DELETE FROM `gameobject` WHERE `id` = @ENTRY;
DELETE FROM `gameobject_template` WHERE `entry` = @ENTRY;

-- rebuild creature version
DELETE FROM `creature` WHERE `id1` = @ENTRY;
DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY;
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;

INSERT INTO `creature_template`
(
    `entry`,
    `name`,
    `subname`,
    `IconName`,
    `gossip_menu_id`,
    `minlevel`,
    `maxlevel`,
    `exp`,
    `faction`,
    `npcflag`,
    `rank`,
    `dmgschool`,
    `BaseAttackTime`,
    `RangeAttackTime`,
    `unit_class`,
    `unit_flags`,
    `type`,
    `type_flags`,
    `lootid`,
    `pickpocketloot`,
    `skinloot`,
    `AIName`,
    `MovementType`,
    `HoverHeight`,
    `RacialLeader`,
    `movementId`,
    `RegenHealth`,
    `CreatureImmunitiesId`,
    `flags_extra`,
    `ScriptName`
)
VALUES
(
    @ENTRY,
    @NAME,
    'Learn any profession',
    'Speak',
    0,
    80,
    80,
    2,
    35,
    1,
    0,
    0,
    2000,
    2000,
    1,
    0,
    9,
    0,
    0,
    0,
    0,
    '',
    0,
    1,
    0,
    0,
    1,
    0,
    0,
    'npc_all_professions_trainer'
);

INSERT INTO `creature_template_model`
(
    `CreatureID`,
    `Idx`,
    `CreatureDisplayID`,
    `DisplayScale`,
    `Probability`,
    `VerifiedBuild`
)
VALUES
(
    @ENTRY,
    0,
    @DISPLAYID,
    1,
    1,
    0
);

UPDATE creature_template_model
SET DisplayScale = 0.75
WHERE CreatureID = @ENTRY