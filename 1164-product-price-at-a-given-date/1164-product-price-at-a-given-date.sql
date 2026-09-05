SELECT 
    p.product_id
    ,COALESCE((
        SELECT pr.new_price
        FROM products pr
        WHERE p.product_id=pr.product_id
            AND pr.change_date<='2019-08-16'
        ORDER BY pr.change_date DESC LIMIT 1
    ),10) AS price
FROM (
    SELECT DISTINCT product_id
    FROM products 
) AS p