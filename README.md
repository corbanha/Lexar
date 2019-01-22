# Lexar

This is a little program written in C++ that takes in a text file and returns a bunch of generated tokens based on what was in the text file.

It has support for quotes and block comments and identifying unique keywords. This output will be fed into a parser to understand the data

For example, the following text:

Facts:
   snap('12345','C. Brown','12 Apple St.','555-1234').
   snap('67890','L. Van Pelt','34 Pear Ave.','555-5678').
   snap('22222','P. Patty','56 Grape Blvd.','555-9999').
   snap('33333','Snoopy','12 Apple St.','555-1234').
   csg('CS101','12345','A').
   csg('CS101','67890','B').
   csg('EE200','12345','C').
   csg('EE200','22222','B+').
  
It would output the following:

(FACTS,"Facts",13)
(COLON,":",13)
(ID,"snap",14)
(LEFT_PAREN,"(",14)
(STRING,"'12345'",14)
(COMMA,",",14)
(STRING,"'C. Brown'",14)
(COMMA,",",14)
(STRING,"'12 Apple St.'",14)
(COMMA,",",14)
(STRING,"'555-1234'",14)
(RIGHT_PAREN,")",14)
(PERIOD,".",14)
(ID,"snap",15)
(LEFT_PAREN,"(",15)
(STRING,"'67890'",15)
(COMMA,",",15)
(STRING,"'L. Van Pelt'",15)
(COMMA,",",15)
(STRING,"'34 Pear Ave.'",15)
(COMMA,",",15)
(STRING,"'555-5678'",15)
(RIGHT_PAREN,")",15)
(PERIOD,".",15)
...
