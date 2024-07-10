# Database

Change the following environment values in the docker-compose.yml to something you want

```yaml
database:
    image: 'postgres:latest'
    container_name: expeditie-db
    ports:
      - 15432:5432
    restart: unless-stopped
    environment:
      - POSTGRES_USER=$POSTGRESS_USER
      - POSTGRES_PASSWORD=$POSTGRES_PASSWORD
      - POSTGRES_DB=$POSTGRES_DB
    ...
```

And also add the user to the table.sql script to make sure the user can access it. 