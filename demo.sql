INSERT INTO PLAYER VALUES(1, 'Logan', 'Gray', 'UC', 71, 150, 20, 'Shake hand');
INSERT INTO PLAYER VALUES(2, 'Ethan', 'Penney', 'UC', 64, 120, 19, 'Shake hand');
INSERT INTO PLAYER VALUES(3, 'Adam', 'Smith', 'RC', 65, 130, 20, 'Shake hand');
INSERT INTO PLAYER VALUES(4, 'Brian', 'Johnson', 'UC', 66, 140, 21, 'pen hold');
INSERT INTO PLAYER VALUES(5, 'Charles', 'Brown', 'RC', NULL, NULL, NULL, NULL);
INSERT INTO PLAYER VALUES(6, 'David', 'Williams', 'UC', 68, 160, 23, 'Shake hand');
INSERT INTO PLAYER VALUES(7, 'Edward', 'Jones', 'UC', 69, 170, 24, NULL);
INSERT INTO PLAYER VALUES(8, 'Frank', 'Miller', 'RC', 70, 180, NULL, 'pen hold');
INSERT INTO PLAYER VALUES(9, 'George', 'Davis', 'RC', 71, NULL, 26, 'Shake hand');
INSERT INTO PLAYER VALUES(10, 'Henry', 'Garcia', 'UC', NULL, 200, 27, 'Shake hand');
INSERT INTO PLAYER VALUES(11, 'Ian', 'Martinez', NULL, 73, 210, 28, 'pen hold');
INSERT INTO PLAYER VALUES(12, 'Jack', 'Rodriguez', 'UC', 74, 220, 29, 'Shake hand');

INSERT INTO MATCH VALUES('2024-05-06 16:23');
INSERT INTO MATCH VALUES('2024-05-07 16:23');
INSERT INTO MATCH VALUES('2024-05-08 16:23');
INSERT INTO MATCH VALUES('2024-05-09 16:23');
INSERT INTO MATCH VALUES('2024-05-10 16:23');
INSERT INTO MATCH VALUES('2024-05-11 16:23');

INSERT INTO PADDLE VALUES('Stiga', 'Nitro', 42);
INSERT INTO PADDLE VALUES('Stiga', 'Hero', 50);
INSERT INTO PADDLE VALUES('Stiga', 'Torch', NULL);

INSERT INTO BALL VALUES('Stiga', 3, 'Orange');
INSERT INTO BALL VALUES('Stiga', 1, NULL);
INSERT INTO BALL VALUES('Penn', 3, 'White');
INSERT INTO BALL VALUES('Penn', 1, 'Orange');
INSERT INTO BALL VALUES('Emoji', 1, 'Dazed');

INSERT INTO PADDLE_COLOR VALUES('Stiga', 'Nitro', 'Red');
INSERT INTO PADDLE_COLOR VALUES('Stiga', 'Nitro', 'Black');
INSERT INTO PADDLE_COLOR VALUES('Stiga', 'Hero', 'Green');
INSERT INTO PADDLE_COLOR VALUES('Stiga', 'Hero', 'Gray');
INSERT INTO PADDLE_COLOR VALUES('Stiga', 'Torch', 'Yellow');
INSERT INTO PADDLE_COLOR VALUES('Stiga', 'Torch', 'Purple');

INSERT INTO GAME VALUES(1, '2024-05-06 16:23', 'Stiga', 'Nitro', 'Stiga', 'Nitro', 1, 2, 2, 1, 1, 9, 11, 'Penn', 3);
INSERT INTO GAME VALUES(2, '2024-05-06 16:23', 'Stiga', 'Nitro', 'Stiga', 'Nitro', 1, 2, 1, 3, 3, 11, 8, 'Penn', 3);
INSERT INTO GAME VALUES(3, '2024-05-06 16:23', 'Stiga', 'Nitro', 'Stiga', 'Nitro', 1, 2, 2, 2, 1, 12, 14, 'Stiga', 1);

INSERT INTO GAME VALUES(1, '2024-05-07 16:23', 'Stiga', 'Hero', 'Stiga', 'Nitro', 4, 7, 2, 1, 1, 9, 11, 'Penn', 3);
INSERT INTO GAME VALUES(2, '2024-05-07 16:23', 'Stiga', 'Hero', 'Stiga', 'Nitro', 4, 7, 1, 3, 3, 11, 8, 'Penn', 3);
INSERT INTO GAME VALUES(3, '2024-05-07 16:23', 'Stiga', 'Torch', 'Stiga', 'Hero', 4, 7, 2, 2, 1, 12, 14, 'Stiga', 1);

INSERT INTO GAME VALUES(1, '2024-05-08 16:23', 'Stiga', 'Torch', 'Stiga', 'Hero', 5, 8, 2, 1, 1, 9, 11, 'Penn', 3);
INSERT INTO GAME VALUES(2, '2024-05-08 16:23', 'Stiga', 'Torch', 'Stiga', 'Hero', 5, 8, 1, 3, 3, 11, 8, 'Penn', 3);
INSERT INTO GAME VALUES(3, '2024-05-08 16:23', NULL, NULL, NULL, NULL, 5, 8, NULL, NULL, NULL, 12, 14, NULL, NULL);

INSERT INTO GAME VALUES(1, '2024-05-09 16:23', 'Stiga', 'Hero', 'Stiga', 'Nitro', 6, 9, 2, 1, 1, 9, 11, 'Penn', NULL);
INSERT INTO GAME VALUES(2, '2024-05-09 16:23', 'Stiga', 'Hero', 'Stiga', 'Nitro', 6, 9, 1, 3, 3, 11, 8, NULL, 3);
INSERT INTO GAME VALUES(3, '2024-05-09 16:23', 'Stiga', 'Torch', 'Stiga', 'Hero', 6, 9, 2, 2, NULL, 12, 14, 'Stiga', 1);

INSERT INTO GAME VALUES(1, '2024-05-10 16:23', 'Stiga', 'Nitro', 'Stiga', 'Torch', 7, 10, 2, NULL, 1, 9, 11, 'Penn', 3);
INSERT INTO GAME VALUES(2, '2024-05-10 16:23', 'Stiga', 'Nitro', 'Stiga', 'Torch', 7, 10, NULL, 3, 3, 11, 8, 'Penn', 3);
INSERT INTO GAME VALUES(3, '2024-05-10 16:23', 'Stiga', 'Hero', 'Stiga', NULL, 7, 10, 2, 2, 1, 12, 14, 'Stiga', 1);

INSERT INTO GAME VALUES(1, '2024-05-11 16:23', 'Stiga', 'Torch', NULL, 'Hero', 8, 11, 2, 1, 1, 9, 11, 'Penn', 3);
INSERT INTO GAME VALUES(2, '2024-05-11 16:23', 'Stiga', NULL, 'Stiga', 'Hero', 8, 11, 1, 3, 3, 11, 8, 'Penn', 3);
INSERT INTO GAME VALUES(3, '2024-05-11 16:23', NULL, 'Nitro', 'Stiga', 'Torch', 8, 11, 2, 2, 1, 12, 14, 'Stiga', 1);

INSERT INTO OWNS VALUES('Stiga', 'Nitro', 1);
INSERT INTO OWNS VALUES('Stiga', 'Nitro', 2);
INSERT INTO OWNS VALUES('Stiga', 'Hero', 5);
INSERT INTO OWNS VALUES('Stiga', 'Torch', 11);
INSERT INTO OWNS VALUES('Stiga', 'Torch', 1);
INSERT INTO OWNS VALUES('Stiga', 'Hero', 2);
INSERT INTO OWNS VALUES('Stiga', 'Nitro', 3);
INSERT INTO OWNS VALUES('Stiga', 'Nitro', 4);
INSERT INTO OWNS VALUES('Stiga', 'Hero', 6);
INSERT INTO OWNS VALUES('Stiga', 'Torch', 12);
INSERT INTO OWNS VALUES('Stiga', 'Torch', 2);
INSERT INTO OWNS VALUES('Stiga', 'Hero', 3);
INSERT INTO OWNS VALUES('Stiga', 'Nitro', 5);
INSERT INTO OWNS VALUES('Stiga', 'Nitro', 6);
INSERT INTO OWNS VALUES('Stiga', 'Hero', 7);
INSERT INTO OWNS VALUES('Stiga', 'Torch', 10);
INSERT INTO OWNS VALUES('Stiga', 'Torch', 3);
INSERT INTO OWNS VALUES('Stiga', 'Hero', 4);