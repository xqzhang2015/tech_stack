<!-- MarkdownTOC -->

- [MySQL docker](#mysql-docker)
  - [Deployment: Docker run](#deployment-docker-run)
  - [Config: Environment Variables](#config-environment-variables)
- [Influxdb](#influxdb)
  - [Deployment: Docker run](#deployment-docker-run-1)
  - [Config: Environment Variables](#config-environment-variables-1)
  - [Example: influxdb](#example-influxdb)

<!-- /MarkdownTOC -->


# MySQL docker
https://hub.docker.com/_/mysql/

### Deployment: Docker run

```sh
$ docker run --name some-mysql -e MYSQL_ROOT_PASSWORD=my-secret-pw -d mysql:tag
```

### Config: Environment Variables

* MYSQL_ROOT_PASSWORD
* MYSQL_DATABASE
* MYSQL_USER, MYSQL_PASSWORD


# Influxdb

https://hub.docker.com/_/influxdb/

### Deployment: Docker run

```sh
$ docker run -p 8086:8086 \
      -v $PWD:/var/lib/influxdb \
      influxdb
```

### Config: Environment Variables

* INFLUXDB_DB

Automatically initializes a database with the name of this environment variable.

* INFLUXDB_HTTP_AUTH_ENABLED

Enables authentication. Either this must be set or auth-enabled = true must be set within the configuration file for any authentication related options below to work.

* INFLUXDB_ADMIN_USER

The name of the admin user to be created. If this is unset, no admin user is created.

* INFLUXDB_ADMIN_PASSWORD

The password for the admin user configured with INFLUXDB_ADMIN_USER. If this is unset, a random password is generated and printed to standard out.

* INFLUXDB_USER

The name of a user to be created with no privileges. If INFLUXDB_DB is set, this user will be granted read and write permissions for that database.

* INFLUXDB_USER_PASSWORD

The password for the user configured with INFLUXDB_USER. If this is unset, a random password is generated and printed to standard out.


### Example: influxdb
https://kublr.com/blog/how-to-utilize-the-heapster-influxdb-grafana-stack-in-kubernetes-for-monitoring-pods/
