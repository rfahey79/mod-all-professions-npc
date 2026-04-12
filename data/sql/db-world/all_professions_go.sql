SET @ENTRY := 190011;
SET @NAME := 'Profession Console';

DELETE FROM `gameobject` WHERE `id` = @ENTRY;
DELETE FROM `gameobject_template` WHERE `entry` = @ENTRY;

INSERT INTO `gameobject_template`
(
    `entry`,
    `type`,
    `displayId`,
    `name`,
    `IconName`,
    `castBarCaption`,
    `unk1`,
    `size`,
    `data0`,
    `data1`,
    `data2`,
    `data3`,
    `data4`,
    `data5`,
    `data6`,
    `data7`,
    `data8`,
    `data9`,
    `data10`,
    `data11`,
    `data12`,
    `data13`,
    `data14`,
    `data15`,
    `data16`,
    `data17`,
    `data18`,
    `data19`,
    `data20`,
    `AIName`,
    `ScriptName`,
    `VerifiedBuild`
)
VALUES
(
    @ENTRY,
    10,
    0,
    @NAME,
    '',
    '',
    '',
    1,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    '',
    'go_all_professions_trainer',
    0
);