<?xml version="1.0"?>

<xsl:stylesheet version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<html>
		<body>
			<head>
				<meta charset="utf-8" />
				<title>Расположение источников</title>
			</head>
			<b>Расположение источников</b>
			<!--<br></br>
			<br></br>-->
			<i><xsl:apply-templates select="comment()"/></i>
			<br></br>
			<br></br>
			<xsl:apply-templates select="TSensSite"/>
		</body>
	</html>
</xsl:template>

<xsl:template match="TSensSite">
	<table border="1" cellspacing="0">
		<!--<tr>
			<td><b><center>number</center></b></td>
			<td><b><center>x</center></b></td>
			<td><b><center>y</center></b></td>
			<td><b><center>sensChar</center></b></td>
		</tr>-->
		<tr>
			<td><b><center>Системный<br></br>номер</center></b></td>
			<td><b><center>X-координата</center></b></td>
			<td><b><center>Y-координата</center></b></td>
			<td><b><center>Номер<br></br>типа<br></br>ИСК</center></b></td>
		</tr>
		<tr>
			<td><b><center></center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center></center></b></td>
		</tr>
		<xsl:apply-templates select="SensSite"/>
	</table>
</xsl:template>

<xsl:template match="SensSite">
	<tr>
		<td><center><xsl:apply-templates select="@number"/></center></td>
		<td><center><xsl:apply-templates select="x"/></center></td>
		<td><center><xsl:apply-templates select="y"/></center></td>
		<td><center><xsl:apply-templates select="sensChar"/></center></td>
	</tr>
</xsl:template>

<xsl:template match="comment()">
	<xsl:value-of select="." />
</xsl:template>

</xsl:stylesheet> 

