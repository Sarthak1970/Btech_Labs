import sqlite3
connection = sqlite3.connect('simple_example.db')

cursor = connection.cursor()


cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    age INTEGER
)
''')

cursor.execute("INSERT INTO users (name, age) VALUES ('Alice', 30)")
cursor.execute("INSERT INTO users (name, age) VALUES ('Bob', 25)")

connection.commit()
def insert_user(name,age):
    cursor.execute("INSERT INTO users (name,age) VALUES (?,?)",(name,age))
    connection.commit()

name=input("Enter name: ")
age=int(input("Enter age: "))
insert_user(name,age)

def clear_table():
    cursor.execute("DROP TABLE IF EXISTS users")
    connection.commit()
    print("The users table has been dropped.")

cursor.execute("SELECT * FROM users")
rows = cursor.fetchall()

for rows in rows:
    print(rows)

option = input("Do you want to delete all records? (yes/no): ")
if option == "yes":
    clear_table()

connection.close()