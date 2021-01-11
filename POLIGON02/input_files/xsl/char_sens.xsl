<?xml version="1.0"?>

<xsl:stylesheet version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<html>
		<body>
			<head>
				<meta charset="utf-8" />
				<title>Типы источников</title>
			</head>
			<b>Типы источников</b>
			<!--<br></br>
			<br></br>-->
			<i><xsl:apply-templates select="comment()"/></i>
			<br></br>
			<br></br>
			<xsl:apply-templates select="TCharSens"/>
		</body>
	</html>
</xsl:template>

<xsl:template match="TCharSens">
    <table border="1" cellspacing="0">
    	<!--<tr>
			<td><b><center>number</center></b></td>
			<td><b><center>hMax</center></b></td>
			<td><b><center>hMin</center></b></td>
			<td><b><center>maxCountTrc</center></b></td>
			<td><b><center>rMax</center></b></td>
			<td><b><center>rMin</center></b></td>
			<td><b><center>trustXY</center></b></td>
			<td><b><center>trustH</center></b></td>
      	</tr>-->
      	<tr>
			<td><b><center>Номер<br></br>типа<br></br>ИСК</center></b></td>
			<td><b><center>Максимальная<br></br>высота</center></b></td>
			<td><b><center>Минимальная<br></br>высота</center></b></td>
			<td><b><center>Максимальное<br></br>количество трасс</center></b></td>
			<td><b><center>Максимальный<br></br>радиус</center></b></td>
			<td><b><center>Минимальный<br></br>радиус</center></b></td>
			<td><b><center>Доверительный<br></br>интервал по координатам</center></b></td>
			<td><b><center>Доверительный<br></br>интервал по высоте</center></b></td>
      	</tr>
      	<tr>
			<td><b><center></center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center></center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center>м</center></b></td>
		</tr>
		<xsl:apply-templates select="CharSens"/>
	</table>
</xsl:template>

<xsl:template match="CharSens">
	<tr>
		<td><center><xsl:apply-templates select="@number"/></center></td>
		<td><center><xsl:apply-templates select="hMax"/></center></td>
		<td><center><xsl:apply-templates select="hMin"/></center></td>
		<td><center><xsl:apply-templates select="maxCountTrc"/></center></td>
		<td><center><xsl:apply-templates select="rMax"/></center></td>
		<td><center><xsl:apply-templates select="rMin"/></center></td>
		<td><center><xsl:apply-templates select="trustXY"/></center></td>
		<td><center><xsl:apply-templates select="trustH"/></center></td>
	</tr>
</xsl:template>

<xsl:template match="comment()">
	<xsl:value-of select="." />
</xsl:template>

</xsl:stylesheet> 

