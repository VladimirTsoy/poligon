<?xml version="1.0"?>

<xsl:stylesheet version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="TPozRegion">
	<html>
		<head>
			<meta charset="utf-8" />
			<title>Тег META, атрибут charset</title>
		</head>
		<body>
    			<h2>PozRegion</h2>
    			<table border="1" cellspacing="0">
      				<tr>
						<td><b><center>number</center></b></td>
						<td><b><center>x</center></b></td>
						<td><b><center>y</center></b></td>
      				</tr>
      				<tr>
						<td><b><center>Номер</center></b></td>
						<td><b><center>X-кордината</center></b></td>
						<td><b><center>Y-кордината</center></b></td>
      				</tr>
      				<tr>
						<td><b><center></center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center>м</center></b></td>
      				</tr>
				<xsl:apply-templates select="PozRegion"/>
    			</table>
		</body>
	</html>
</xsl:template>

<xsl:template match="PozRegion">
	<tr>
		<td><center><xsl:apply-templates select="@number"/></center></td>
		<td><center><xsl:apply-templates select="x"/></center></td>
		<td><center><xsl:apply-templates select="y"/></center></td>
	</tr>
</xsl:template>

</xsl:stylesheet> 

