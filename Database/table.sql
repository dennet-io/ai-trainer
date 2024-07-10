-- Table: public.scores

-- DROP TABLE IF EXISTS public.scores;

CREATE TABLE IF NOT EXISTS public.scores
(
    id bigint NOT NULL DEFAULT nextval('scores_id_seq'::regclass),
    team character varying(4) COLLATE pg_catalog."default",
    elapsed_time numeric(10,2) NOT NULL,
    difference numeric(10,6) NOT NULL,
    goal_r integer NOT NULL,
    goal_g integer NOT NULL,
    goal_b integer NOT NULL,
    goal_a integer NOT NULL,
    actual_r integer NOT NULL,
    actual_g integer NOT NULL,
    actual_b integer NOT NULL,
    actual_a integer NOT NULL,
    created_at timestamp with time zone DEFAULT CURRENT_TIMESTAMP,
    CONSTRAINT scores_pkey PRIMARY KEY (id)
)

TABLESPACE pg_default;

ALTER TABLE IF EXISTS public.scores
    OWNER to $YOUR_USER;
