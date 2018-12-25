-- MySQL dump 10.14  Distrib 5.5.60-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: rookery
-- ------------------------------------------------------
-- Server version	5.5.60-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `bird_orders`
--

DROP TABLE IF EXISTS `bird_orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bird_orders` (
  `order_id` int(11) NOT NULL AUTO_INCREMENT,
  `scientific_name` varchar(255) DEFAULT NULL,
  `brief_description` text,
  `order_image` blob,
  PRIMARY KEY (`order_id`),
  UNIQUE KEY `scientific_name` (`scientific_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bird_orders`
--

LOCK TABLES `bird_orders` WRITE;
/*!40000 ALTER TABLE `bird_orders` DISABLE KEYS */;
/*!40000 ALTER TABLE `bird_orders` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `birds`
--

DROP TABLE IF EXISTS `birds`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `birds` (
  `bird_id` int(11) NOT NULL AUTO_INCREMENT,
  `scientific_name` varchar(255) COLLATE latin1_bin DEFAULT NULL,
  `common_name` varchar(50) COLLATE latin1_bin DEFAULT NULL,
  `family_id` int(11) DEFAULT NULL,
  `description` text COLLATE latin1_bin,
  PRIMARY KEY (`bird_id`),
  UNIQUE KEY `scientific_name` (`scientific_name`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1 COLLATE=latin1_bin;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `birds`
--

LOCK TABLES `birds` WRITE;
/*!40000 ALTER TABLE `birds` DISABLE KEYS */;
INSERT INTO `birds` VALUES (1,'Charadrius vociferus','Killdeer',NULL,NULL),(2,'Gavia immer','Great Norhern Loon',NULL,NULL),(3,'Aix sponsa','Wood Duck',NULL,NULL),(4,'Chordeiles minor','Common Nightawk',NULL,NULL),(5,'Sitta carolinensis','White-breasted Nuthatch',NULL,NULL),(6,'Apteryx mantelli','North Island Brown Kiwi',NULL,NULL);
/*!40000 ALTER TABLE `birds` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `birds_bill_shapes`
--

DROP TABLE IF EXISTS `birds_bill_shapes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `birds_bill_shapes` (
  `bill_id` char(2) DEFAULT NULL,
  `bill_shape` char(25) DEFAULT NULL,
  `bill_example` blob,
  UNIQUE KEY `bill_id` (`bill_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `birds_bill_shapes`
--

LOCK TABLES `birds_bill_shapes` WRITE;
/*!40000 ALTER TABLE `birds_bill_shapes` DISABLE KEYS */;
/*!40000 ALTER TABLE `birds_bill_shapes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `birds_body_shapes`
--

DROP TABLE IF EXISTS `birds_body_shapes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `birds_body_shapes` (
  `body_id` char(3) DEFAULT NULL,
  `body_shape` char(25) DEFAULT NULL,
  `body_example` blob,
  UNIQUE KEY `body_id` (`body_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `birds_body_shapes`
--

LOCK TABLES `birds_body_shapes` WRITE;
/*!40000 ALTER TABLE `birds_body_shapes` DISABLE KEYS */;
/*!40000 ALTER TABLE `birds_body_shapes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `birds_wing_shapes`
--

DROP TABLE IF EXISTS `birds_wing_shapes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `birds_wing_shapes` (
  `wing_id` char(2) CHARACTER SET latin1 COLLATE latin1_bin DEFAULT NULL,
  `wing_shape` char(25) CHARACTER SET latin1 COLLATE latin1_bin DEFAULT NULL,
  `wing_example` blob,
  UNIQUE KEY `wing_id` (`wing_id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `birds_wing_shapes`
--

LOCK TABLES `birds_wing_shapes` WRITE;
/*!40000 ALTER TABLE `birds_wing_shapes` DISABLE KEYS */;
/*!40000 ALTER TABLE `birds_wing_shapes` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-12-25  5:12:21
