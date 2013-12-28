CREATE 
    ALGORITHM = UNDEFINED 
    DEFINER = `wuhaotian`@`%` 
    SQL SECURITY DEFINER
VIEW `final_overall` AS
    select 
        `final_restaurant`.`id` AS `restaurant_id`,
        count(distinct `final_rate`.`id`) AS `count`,
        ifnull(avg(`final_rate`.`star`), 0) AS `star`,
        ifnull(avg(`final_rate`.`service`), 0) AS `service`,
        ifnull(avg(`final_rate`.`flavor`), 0) AS `flavor`,
        ifnull(avg(`final_rate`.`environment`), 0) AS `environment`,
        ifnull(((((avg(`final_rate`.`star`) * 0.4) + (avg(`final_rate`.`service`) * 0.2)) + (avg(`final_rate`.`environment`) * 0.2)) + (avg(`final_rate`.`flavor`) * 0.2)),
                0) AS `total`
    from
        (`final_restaurant`
        left join `final_rate` ON ((`final_rate`.`restaurant_id` = `final_restaurant`.`id`)))
    group by `final_restaurant`.`id`
