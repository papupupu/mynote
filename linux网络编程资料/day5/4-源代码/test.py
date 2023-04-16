'''
import MySQLdb

# 连接到数据库
conn = MySQLdb.connect(
    host="localhost",
    user="papupupu",
    password="123456",
    db="test"
)

# 创建一个游标对象
cursor = conn.cursor()

# 构建 SQL 插入语句
data = {"name": "John", "age": 30, "gender": "male", "height": 180}
keys = ["name", "age", "gender"]
values = [data[k] for k in keys]
sql = "INSERT INTO my_table ({}) VALUES ({})".format(
    ",".join(keys),
    ",".join(["%s"] * len(values))
)

# 执行 SQL 插入语句
cursor.execute(sql, values)

# 提交更改
conn.commit()

# 关闭游标和数据库连接
cursor.close()
conn.close()
'''
import re

my_string = str("This is a \\r\\nmulti-line string.")
my_string = re.sub(r"\\r\\n", "", my_string)
print(my_string)
print("end")
