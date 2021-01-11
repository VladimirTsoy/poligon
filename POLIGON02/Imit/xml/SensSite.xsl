<?xml version="1.0"?>

<xsl:stylesheet version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="TSensSite">
	<html>
		<head>
			<meta charset="utf-8" />
			<title>Тег META, атрибут charset</title>
		</head>
		<body>
    			<h2>SensSite</h2>
    			<table border="1" cellspacing="0">
      				<tr>
						<td><b><center>number</center></b></td>
						<td><b><center>x</center></b></td>
						<td><b><center>y</center></b></td>
						<td><b><center>azimut</center></b></td>
						<td><b><center>sensChar</center></b></td>
      				</tr>
      				<tr>
						<td><b><center>Номер</center></b></td>
						<td><b><center>X-координата</center></b></td>
						<td><b><center>Y-координата</center></b></td>
						<td><b><center>Азимут</center></b></td>
						<td><b><center>Тип источника</center></b></td>
      				</tr>
      				<tr>
						<td><b><center></center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center>рад</center></b></td>
						<td><b><center></center></b></td>
      				</tr>
				<xsl:apply-templates select="SensSite"/>
    			</table>
		</body>
	</html>
</xsl:template>

<xsl:template match="SensSite">
	<tr>
		<td><center><xsl:apply-templates select="@number"/></center></td>
		<td><center><xsl:apply-templates select="x"/></center></td>
		<td><center><xsl:apply-templates select="y"/></center></td>
		<td><center><xsl:apply-templates select="azimut"/></center></td>
		<td><center><xsl:apply-templates select="sensChar"/></center></td>
	</tr>
</xsl:template>

</xsl:stylesheet> 

