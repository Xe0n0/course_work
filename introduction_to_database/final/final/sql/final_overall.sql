CREATE 
    ALGORITHM = UNDEFINED 
    DEFINER = `wuhaotian`@`%` 
    SQL SECURITY DEFINER
VIEW `test2`.`final_overall` AS
    select 
        `test2`.`final_restaurant`.`id` AS `restaurant_id`,
        count(distinct `test2`.`final_rate`.`id`) AS `count`,
        ifnull(avg(`test2`.`final_rate`.`star`), 0) as star,
        ifnull(avg(`test2`.`final_rate`.`service`), 0) as service,
        ifnull(avg(`test2`.`final_rate`.`flavor`), 0) as flavor,
        ifnull(avg(`test2`.`final_rate`.`environment`), 0) as environment,
        ifnull(((`test2`.`final_rate`.`star` * 0.4 + `test2`.`final_rate`.`service` * 0.2) + `test2`.`final_rate`.`environment` * 0.2 + `test2`.`final_rate`.`flavor` * 0.2),
                0) AS `total`
    from
        (`test2`.`final_restaurant`
        left join `test2`.`final_rate` ON ((`test2`.`final_rate`.`restaurant_id` = `test2`.`final_restaurant`.`id`)))
    group by `test2`.`final_restaurant`.`id`
