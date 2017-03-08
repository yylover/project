import functools
import time, uuid, logging

from datetime import date, datetime, timedelta
import mysql.connector
import threading
from mysql.connector import errorcode


# import datetime

class Dict(dict):
    def __init__(self, names=(), values=(), **kw):
        super(Dict, self).__init__(**kw)
        for k, v in zip(names, values):
            self[k] = v

    def __getattr__(self, item):
        try:
            return self[key]
        except KeyError:
            raise AttributeError(r"Dict object has no attribute '%s" %key)

    def __setattr__(self, key, value):
        self[key] = value




def next_id(t=None):
    if t is None:
        t = time.time()
    return '%015d%s000' % (int(t * 1000), uuid.uuid4().hex)


class DBError(Exception):
    pass


class MultiColumnsError(Exception):
    pass


class _LasyConnection(object):
    def __init__(self):
        self.connection = None

    def cursor(self):
        if self.connection is None:
            connection = engine.connect()

            self.connection = connection
        return self.connection.cursor()


engine = None


class _Engine(object):
    def __init__(self, connect):
        self._connect = connect

    def connect(self):
        return self._connect()


# 创建于数据库的连接
def create_engine(user, password, database, host='127.0.0.1', port=3306, **kw):
    logging.info("create_engine")
    global engine
    if engine is not None:
        raise DBError("Engine is already exists")
    params = dict(user=user, password=password, database=database, host=host, port=port)
    defaults = dict(use_unicode=True, charset='utf8', collation='utf8_general_ci', autocommit=False)

    # for k, v in defaults.iteritems():
    #     params[k] = kw.pop(k, v)
    params.update(defaults)
    params.update(kw)
    params['buffered'] = True

    engine = _Engine(lambda: mysql.connector.connect(**params))
    logging.info('Init mysql engine <%s> ok.' % hex(id(engine)))


# 懒加载连接器
class __LasyConnection(object):
    def __init__(self):
        self.connection = None

    def cursor(self):
        if self.connection is None:
            connection = engine.connect()
            logging.info("open connection <%s> .." % hex(id(connection)))
            self.connection = connection
        return self.connection.cursor()

    def commit(self):
        self.connection.commit()

    def rollback(self):
        self.connection.rollback()

    def cleanup(self):
        if self.connection:
            connection = self.connection
            self.connection = None

            logging.info('close connection <%s>...' % hex(id(connection)))
            connection.close()


class _DbCtx(threading.local):
    '''
    Thread local object that holds connection info
    '''

    def __init__(self):
        self.connection = None
        self.transactions = 0

    def is_init(self):
        return not self.connection is None

    def init(self):
        self.connection = _LasyConnection()
        self.transactions = 0

    def cleanup(self):
        self.connection.cleanup()
        self.transactions = 0

    def cursor(self):
        return self.connection.cursor()

_db_ctx = _DbCtx()

class _ConnectionCtx(object):
    def __enter__(self):
        global _db_ctx
        self.should_cleanup = False
        if not _db_ctx.is_init()
            _db_ctx..init()
            self.should_cleanup = True
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        global _db_ctx
        if self.should_cleanup:
            _db_ctx.cleanup()


def with_connection(func):
    @functools.wraps(func)
    def _wrapper(*args, **kw):
        with _ConnectionCtx()
            return func(*args, **kw)
    return _wrapper

class _TransactionCtx(object):
    def __enter__(self):
        global _db_ctx
        self.should_close_conn = False
        if not _db_ctx.is_init():
            _db_ctx.init()
            self.should_close_conn = True
        _db_ctx.transactions = _db_ctx.transactions + 1
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        global _db_ctx
        _db_ctx.transactions = _db_ctx.transactions - 1
        try:
            if _db_ctx.transactions == 0:
                if exc_type is None:
                    self.commit()
                else
                    self.rollback()
        finally:
            if self.should_close_conn:
                _db_ctx.cleanup()

    def commit(self):
        global _db_ctx
        try:
            _db_ctx.connection.commit()
        except:
            _db_ctx.connection.rollback()
            raise

    def rollback(self):
        global _db_ctx:
        _db_ctx.connection.rollback()

def with_transaction(func):
    @functools.wraps(func)
    def _wrapper(*args, **kw):
        _start = time.time()
        with _TransactionCtx():
            return func(*args, **kw)

    return  _wrapper

def _select(sql, first, *args):
    global _db_ctx





TABLES = {}
TABLES['employees'] = (
    "CREATE TABLE `employees` ("
    "  `emp_no` int(11) NOT NULL AUTO_INCREMENT,"
    "  `birth_date` date NOT NULL,"
    "  `first_name` varchar(14) NOT NULL,"
    "  `last_name` varchar(16) NOT NULL,"
    "  `gender` enum('M','F') NOT NULL,"
    "  `hire_date` date NOT NULL,"
    "  PRIMARY KEY (`emp_no`)"
    ") ENGINE=InnoDB")

TABLES['departments'] = (
    "CREATE TABLE `departments` ("
    "  `dept_no` char(4) NOT NULL,"
    "  `dept_name` varchar(40) NOT NULL,"
    "  PRIMARY KEY (`dept_no`), UNIQUE KEY `dept_name` (`dept_name`)"
    ") ENGINE=InnoDB")

TABLES['salaries'] = (
    "CREATE TABLE `salaries` ("
    "  `emp_no` int(11) NOT NULL,"
    "  `salary` int(11) NOT NULL,"
    "  `from_date` date NOT NULL,"
    "  `to_date` date NOT NULL,"
    "  PRIMARY KEY (`emp_no`,`from_date`), KEY `emp_no` (`emp_no`),"
    "  CONSTRAINT `salaries_ibfk_1` FOREIGN KEY (`emp_no`) "
    "     REFERENCES `employees` (`emp_no`) ON DELETE CASCADE"
    ") ENGINE=InnoDB")

TABLES['dept_emp'] = (
    "CREATE TABLE `dept_emp` ("
    "  `emp_no` int(11) NOT NULL,"
    "  `dept_no` char(4) NOT NULL,"
    "  `from_date` date NOT NULL,"
    "  `to_date` date NOT NULL,"
    "  PRIMARY KEY (`emp_no`,`dept_no`), KEY `emp_no` (`emp_no`),"
    "  KEY `dept_no` (`dept_no`),"
    "  CONSTRAINT `dept_emp_ibfk_1` FOREIGN KEY (`emp_no`) "
    "     REFERENCES `employees` (`emp_no`) ON DELETE CASCADE,"
    "  CONSTRAINT `dept_emp_ibfk_2` FOREIGN KEY (`dept_no`) "
    "     REFERENCES `departments` (`dept_no`) ON DELETE CASCADE"
    ") ENGINE=InnoDB")

TABLES['dept_manager'] = (
    "  CREATE TABLE `dept_manager` ("
    "  `dept_no` char(4) NOT NULL,"
    "  `emp_no` int(11) NOT NULL,"
    "  `from_date` date NOT NULL,"
    "  `to_date` date NOT NULL,"
    "  PRIMARY KEY (`emp_no`,`dept_no`),"
    "  KEY `emp_no` (`emp_no`),"
    "  KEY `dept_no` (`dept_no`),"
    "  CONSTRAINT `dept_manager_ibfk_1` FOREIGN KEY (`emp_no`) "
    "     REFERENCES `employees` (`emp_no`) ON DELETE CASCADE,"
    "  CONSTRAINT `dept_manager_ibfk_2` FOREIGN KEY (`dept_no`) "
    "     REFERENCES `departments` (`dept_no`) ON DELETE CASCADE"
    ") ENGINE=InnoDB")

TABLES['titles'] = (
    "CREATE TABLE `titles` ("
    "  `emp_no` int(11) NOT NULL,"
    "  `title` varchar(50) NOT NULL,"
    "  `from_date` date NOT NULL,"
    "  `to_date` date DEFAULT NULL,"
    "  PRIMARY KEY (`emp_no`,`title`,`from_date`), KEY `emp_no` (`emp_no`),"
    "  CONSTRAINT `titles_ibfk_1` FOREIGN KEY (`emp_no`)"
    "     REFERENCES `employees` (`emp_no`) ON DELETE CASCADE"
    ") ENGINE=InnoDB")


def createTableTest(cursor):
    for v in TABLES.itervalues():
        try:
            cursor.execute(v)
        except mysql.connector.Error as err:
            if err.errno == errorcode.ER_TABLE_EXISTS_ERROR:
                print "table exists", err
            else:
                print err


def insertTableTest(cursor, sql, data):
    cursor.execute(sql, data)


def queryTableTest(cursor):
    query = ("SELECT first_name, last_name, hire_date FROM employees "
             "WHERE hire_date BETWEEN %s AND %s")
    hire_start = date(1999, 1, 1)
    hire_end = date(2018, 12, 31)
    cursor.execute(query, (hire_start, hire_end))

    for (first_name, last_name, hire_date) in cursor:
        print("{} {} was hired on {:%d %b %Y}".format(last_name, first_name, hire_date))



if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG,
                        format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                        datefmt='%a, %d %b %Y %H:%M:%S',
                        filename='myapp.log',
                        filemode='w')

    create_engine("root", "", "awesome")

    connect = engine.connect()
    cursor = connect.cursor()

    createTableTest(cursor)

    add_sql = ("INSERT INTO employees "
               "(first_name, last_name, hire_date, gender, birth_date) "
               "VALUES (%s, %s, %s, %s, %s)")
    add_salary = ("INSERT INTO salaries "
                  "(emp_no, salary, from_date, to_date) "
                  "VALUES (%(emp_no)s, %(salary)s, %(from_date)s, %(to_date)s)")

    tomorrow = datetime.now().date() + timedelta(days=1)
    data_employee = ('Geert', 'Vanderkelen', tomorrow, 'M', date(1999, 6, 14))
    insertTableTest(cursor, add_sql, data_employee)

    emp_no = cursor.lastrowid
    data_salary = {'emp_no': emp_no, 'salary': 5000, 'from_date': tomorrow, 'to_date': date(9999, 1, 1)}
    insertTableTest(cursor, add_salary, data_salary)

    queryTableTest(cursor)

    connect.commit()
    cursor.close()
    connect.close()

    dict1 = {'a': 2, 'b': 3}
    d2 = {'c': 3, 'd': 4, 'a': 5}
    print  dict1
    print d2
    dict1.update(d2)
    print

