# Phalcon Unit Tests

Welcome to the Phalcon Testing Suite.

This folder contains all the tests for the Phalcon Framework. 

## Getting Started

This testing suite uses [Travis CI][0] for each run. Every commit pushed to this repository will queue a build into the continuous integration service and will run all tests to ensure that everything is going well and the project is stable.

The testing suite can be run on your own machine. The only dependencies for running the testing suite are [nanobox][9] and [Codeception][1]. Nanobox can also be used for developing Phalcon, and its installation instructions can be found [in the Nanobox documentation][10]. Codeception can be installed using [Composer][6]:

```sh
# run this command from project root
composer install --prefer-source
```

You can read more about installing and configuring Codeception from the following resources:

- [Codeception Introduction][2]
- [Codeception Console Commands][3]

The container based environment contains all the services you need to write and run your tests. These services are:
- Beanstalkd
- Memcached
- Mongodb
- Mysql
- Postgresql
- Redis

The PHP extensions enabled are:
- apcu
- ctype
- curl
- dom
- fileinfo
- gd
- gmp
- gettext
- imagick
- iconv
- igbinary
- json
- memcached
- mbstring
- mongodb
- opcache
- phar
- pdo
- pdo_mysql
- pdo_pgsql
- pdo_sqlite
- redis
- session
- simplexml
- tokenizer
- yaml
- zephir_parser
- xdebug
- xml
- xmlwriter
- zip
- zlib

## Start the environment
We will need a terminal window, so open one if you don't have one already and navigate to the folder where you have cloned the repository (or a fork of it)

Nanobox reads its configuration, so as to start the environment, from a file called `boxfile.yml` located at the root of your folder. By default the file is not there to allow for more flexibility. We have two setup files, one for PHP 7.2 and one for PHP 7.3. If you wish to set up an environment for Phalcon using PHP 7.2, you can copy the relevant file at the root of your folder:

```bash
cp -v ./tests/_ci/nanobox/boxfile.7.2.yml ./boxfile.yml
```

You can also create a 7.3 environment by copying the relevant file.

Run
```bash
nanobox run
```

The process will take a while (for the first time) and once it is done you will be inside the environment. The prompt of your terminal will be:

```bash
Preparing environment :

....

                                   **
                                ********
                             ***************
                          *********************
                            *****************
                          ::    *********    ::
                             ::    ***    ::
                           ++   :::   :::   ++
                              ++   :::   ++
                                 ++   ++
                                    +
                    _  _ ____ _  _ ____ ___  ____ _  _
                    |\ | |__| |\ | |  | |__) |  |  \/
                    | \| |  | | \| |__| |__) |__| _/\_

--------------------------------------------------------------------------------
+ You are in a Linux container
+ Your local source code has been mounted into the container
+ Changes to your code in either the container or desktop will be mirrored
+ If you run a server, access it at >> 172.18.0.2
--------------------------------------------------------------------------------

/app $
```

Now that zephir is in your environment, you can check it by typing:
```bash
/app $ zephir
```

This should show you the help screen. You can now compile the extension:
```bash
/app $ zephir fullclean
/app $ zephir build

```

After the compilation is completed, you can check if the extension is loaded:
```bash
/app $ php -m | grep phalcon
```

## Setup databases
The SQL dump files are located under `tests/_data/assets/db/schemas`. When importing your Postgresql database, please make sure you use the file suffixed with `*nanobox`. You can run the following commands from your nanobox environment

```sh
/app $ cat ./tests/_data/assets/db/schemas/mysql_schema.sql | mysql -u root gonano

/app $ psql -U nanobox gonano -q -f ./tests/_data/assets/db/schemas/postgresql_schema.sql

/app $ sqlite3 ./tests/_output/phalcon_test.sqlite < ./tests/_data/assets/db/schemas/sqlite_schema.sql
/app $ sqlite3 ./tests/_output/translations.sqlite < ./tests/_data/assets/db/schemas/sqlite_translations_schema.sql
```

## Run tests

First you need to re-generate base classes for all suites:

```sh
/app $ codecept build
```

Once the database is created, run the tests on a terminal:

```sh
/app $ codecept run
# OR
/app $ codecept run --debug # Detailed output
```

Execute `unit` test with `run unit` command:

```sh
/app $ codecept run unit
```

Execute all tests from a folder:

```sh
/app $ codecept run tests/unit/some/folder/
```

Execute single test:

```sh
/app $ codecept run tests/unit/some/folder/some/test/file.php
```

## Todo
- [ ] Add more information in this readme
- [ ] Write tests for the skipped ones in the suite
- [ ] Tests for foreign keys cascade in the ORM
- [ ] Tests for many-to-many relations
- [ ] Tests for `+=`, `-=`, `*=`, `/=`, `++`, `--` in Volt
- [ ] Tests for `Alc::allow('*', '*', 'index')`
- [ ] Tests for `Alc::allow('*', '*', '*')`
- [ ] Tests for `Alc::deny('user', '*', '*')` - should deny all resources

## Help

**Note:** Cache-related tests are slower than others tests because they use wait states (sleep command) to expire generated caches.

<hr>
Please report any issue if you find out bugs or memory leaks.


Thanks!

<3 Phalcon Framework Team

[0]: https://travis-ci.org/
[1]: http://codeception.com/
[2]: http://codeception.com/docs/01-Introduction
[3]: http://codeception.com/docs/reference/Commands
[6]: http://getcomposer.org
[7]: https://github.com/phalcon/cphalcon/tree/master/tests/_proxies
[8]: https://wiki.archlinux.org/index.php/Environment_variables
[9]: https://nanobox.io/
[10]: https://docs.nanobox.io/install/
