BEGIN TRANSACTION;

DROP TABLE IF EXISTS puntajes CASCADE;
CREATE TABLE puntajes (
	pk bigserial NOT NULL,
	rut int NOT NULL,
	nem int NOT NULL,
	ranking int NOT NULL,
	matematica int NOT NULL,
	lenguaje int NOT NULL,
	ciencias int NOT NULL,
	historia int NOT NULL,
	UNIQUE (rut),
	PRIMARY KEY (pk)
);

COMMIT;

