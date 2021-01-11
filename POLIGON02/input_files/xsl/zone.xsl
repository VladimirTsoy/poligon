<?xml version="1.0"?>

<xsl:stylesheet version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<html>
		<body>
			<head>
				<meta charset="utf-8" />
				<title>Зоны</title>
			</head>
			<b>Зоны</b>
			<!--<br></br>
			<br></br>-->
			<i><xsl:apply-templates select="comment()"/></i>
			<br></br>
			<br></br>
			<xsl:apply-templates select="zones"/>
		</body>
	</html>
</xsl:template>

<xsl:template match="zones">
	<table border="1" cellspacing="0">
		<!--<tr>
			<td><b><center>zone_number</center></b></td>
			<td><b><center>r</center></b></td>
			<td><b><center>g</center></b></td>
			<td><b><center>b</center></b></td>
			<td><b><center>a</center></b></td>
			<td><b><center>point_number</center></b></td>
			<td><b><center>x</center></b></td>
			<td><b><center>y</center></b></td>
		</tr>-->
		<tr>
			<td><b><center>Номер<br></br>зоны</center></b></td>
			<td><b><center>Составляющая<br></br>красного<br></br>цвета</center></b></td>
			<td><b><center>Составляющая<br></br>зеленого<br></br>цвета</center></b></td>
			<td><b><center>Составляющая<br></br>синего<br></br>цвета</center></b></td>
			<td><b><center>Прозрачность</center></b></td>
			<td><b><center>Номер<br></br>точки</center></b></td>
			<td><b><center>X-координата<br></br>точки</center></b></td>
			<td><b><center>Y-координата<br></br>точки</center></b></td>
      	</tr>
      	<tr>
			<td><b><center></center></b></td>
			<td><b><center></center></b></td>
			<td><b><center></center></b></td>
			<td><b><center></center></b></td>
			<td><b><center></center></b></td>
			<td><b><center></center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center>м</center></b></td>
		</tr>
		<xsl:apply-templates select="zone"/>
	</table>
</xsl:template>

<xsl:template match="zone">
	<tr>
		<td>
			<xsl:attribute name="rowSpan"><xsl:value-of select="count(point)"/></xsl:attribute>
			<center><xsl:apply-templates select="@number"/></center>
		</td>
		<td>
			<xsl:attribute name="rowSpan"><xsl:value-of select="count(point)"/></xsl:attribute>
			<center><xsl:apply-templates select="r"/></center>
		</td>
		<td>
			<xsl:attribute name="rowSpan"><xsl:value-of select="count(point)"/></xsl:attribute>
			<center><xsl:apply-templates select="g"/></center>
		</td>
		<td>
			<xsl:attribute name="rowSpan"><xsl:value-of select="count(point)"/></xsl:attribute>
			<center><xsl:apply-templates select="b"/></center>
		</td>
		<td>
			<xsl:attribute name="rowSpan"><xsl:value-of select="count(point)"/></xsl:attribute>
			<center><xsl:apply-templates select="a"/></center>
		</td>
		<xsl:if test="count(point)=0">
			<td><center></center></td>
			<td><center></center></td>
			<td><center></center></td>
		</xsl:if>
		<xsl:apply-templates select="point[position() = 1]"/>
	</tr>
	<xsl:apply-templates select="point[position() != 1]"/>
</xsl:template>

<xsl:template match="point">
	<xsl:if test="position() = 1">
		<td><center><xsl:apply-templates select="@number"/></center></td>
		<td><center><xsl:apply-templates select="x"/></center></td>
		<td><center><xsl:apply-templates select="y"/></center></td>
	</xsl:if>
	<xsl:if test="position() != 1">
		<tr>
			<td><center><xsl:apply-templates select="@number"/></center></td>
			<td><center><xsl:apply-templates select="x"/></center></td>
			<td><center><xsl:apply-templates select="y"/></center></td>
		</tr>
	</xsl:if>
</xsl:template>

<xsl:template match="comment()">
	<xsl:value-of select="." />
</xsl:template>

</xsl:stylesheet> 

