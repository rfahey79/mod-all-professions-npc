SET @ENTRY := 190011;
SET @NAME := 'Profession Master';
SET @DISPLAYID := 11686; -- placeholder example, replace with the box model you want

DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
DELETE FROM `creature_template_model` WHERE `CreatureID` = @ENTRY;

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
) VALUES
(
    @ENTRY, @NAME, 'Learn any profession', NULL, 0, 80, 80, 2, 35, 1, 0, 0, 2000, 0, 1, 0, 7, 138936390, 0, 0, 0, '', 0, 1, 0, 0, 1, 0, 0, 'npc_all_professions_trainer'
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