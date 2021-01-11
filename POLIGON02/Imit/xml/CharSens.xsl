<?xml version="1.0"?>

<xsl:stylesheet version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="TCharSens">
	<html>
		<head>
			<meta charset="utf-8" />
			<title>Тег META, атрибут charset</title>
		</head>
		<body>
    			<h2>CharSens</h2>
    			<table border="1" cellspacing="0">
      				<tr>
						<td><b><center>number</center></b></td>
						<td><b><center>hMax</center></b></td>
						<td><b><center>maxCountTrc</center></b></td>
						<td><b><center>rMax</center></b></td>
						<td><b><center>rMin</center></b></td>
						<td><b><center>azimutMax</center></b></td>
						<td><b><center>azimutMin</center></b></td>
						<td><b><center>trustXY</center></b></td>
						<td><b><center>trustH</center></b></td>
      				</tr>
      				<tr>
						<td><b><center>Номер</center></b></td>
						<td><b><center>Максимальная<br>высота</br></center></b></td>
						<td><b><center>Максимальное<br>количество трасс</br></center></b></td>
						<td><b><center>Максимальный<br>радиус</br></center></b></td>
						<td><b><center>Минимальный<br>радиус</br></center></b></td>
						<td><b><center>Максимальный<br>азимут</br></center></b></td>
						<td><b><center>Минимальный<br>азимут</br></center></b></td>
						<td><b><center>Доверительный<br>интервал по</br>координатам</center></b></td>
						<td><b><center>Доверительный<br>интервал по</br>высоте</center></b></td>
      				</tr>
      				<tr>
						<td><b><center></center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center></center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center>рад</center></b></td>
						<td><b><center>рад</center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center>м</center></b></td>
      				</tr>
				<xsl:apply-templates select="CharSens"/>
    			</table>
		</body>
	</html>
</xsl:template>

<xsl:template match="CharSens">
	<tr>
		<td><center><xsl:apply-templates select="@number"/></center></td>
		<td><center><xsl:apply-templates select="hMax"/></center></td>
		<td><center><xsl:apply-templates select="maxCountTrc"/></center></td>
		<td><center><xsl:apply-templates select="rMax"/></center></td>
		<td><center><xsl:apply-templates select="rMin"/></center></td>
		<td><center><xsl:apply-templates select="azimutMax"/></center></td>
		<td><center><xsl:apply-templates select="azimutMin"/></center></td>
		<td><center><xsl:apply-templates select="trustXY"/></center></td>
		<td><center><xsl:apply-templates select="trustH"/></center></td>
	</tr>
</xsl:template>

</xsl:stylesheet> 

