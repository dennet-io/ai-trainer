#     Copyright (C) 2024 Joeri Kortenhorst
#
#     This program is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     This program is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with this program.  If not, see <https://www.gnu.org/licenses/>.

import psycopg2
import configparser


class Database:
    """
    Database helper that checks if the PostgreSQL database is running. If the connection is opened
    succesfully, the insert method can be used in order to insert a new score into
    the database.

    :param path: path to a config file in ini format.
    Section name should be 'db' and have the
    following fields:
    - dbname
    - user
    - password
    - host
    - port
    """
    config: dict[str, str]

    def __init__(self, path: str):
        self.config = self.read_config(path, 'db')
        self.conn = psycopg2.connect(dbname=self.config['dbname'],
                                     user=self.config['user'],
                                     password=self.config['password'],
                                     host=self.config['host'],
                                     port=self.config['port'])

    def __del__(self):
        self.conn.close()

    @staticmethod
    def read_config(path: str, section_name: str) -> dict[str, str]:
        """
        Reads the config file in ini format and returns it as a dictionary.
        :param path:
        :param section_name:
        :return:
        """
        config = configparser.ConfigParser()
        config.read(path)

        if config.has_section(section_name):
            return {option: config.get(section_name, option) for option in config.options(section_name)}
        else:
            raise ValueError(f"Section '{section_name}' not found in {path}")

    def insert(self, elapsed_time: float, difference: float, goal_r: int, goal_g: int, goal_b: int, goal_a: int,
               actual_r: int, actual_g: int, actual_b: int, actual_a: int):
        """
        Insert a new score into the database.
        :param elapsed_time:
        :param difference:
        :param goal_r:
        :param goal_g:
        :param goal_b:
        :param goal_a:
        :param actual_r:
        :param actual_g:
        :param actual_b:
        :param actual_a:
        :return:
        """
        cur = self.conn.cursor()
        insert_string = f"""INSERT INTO public.scores (elapsed_time, difference, goal_r, goal_g, goal_b, goal_a, actual_r, actual_g, actual_b, actual_a) VALUES ({elapsed_time}, {difference}, {goal_r}, {goal_g}, {goal_b}, {goal_a}, {actual_r} , {actual_g}, {actual_b}, {actual_a})"""
        print(insert_string)
        try:
            cur.execute(insert_string)
            self.conn.commit()
        except Exception as e:
            print("An error occured:", e)
            self.conn.rollback()

        cur.close()
