-- Power system (pkodev.mod.power)
-- Calculate player's character power amount
function CalculatePower(role)
	
	-- Get some character attributes
	local str = GetChaAttr(role, ATTR_STR)
	local agi = GetChaAttr(role, ATTR_AGI)
	local con = GetChaAttr(role, ATTR_CON)
	local spr = GetChaAttr(role, ATTR_STA)
	local acc = GetChaAttr(role, ATTR_DEX)
	
	-- Power formula
	local formula =  ( str + agi + con + spr + acc )
	
	-- Return calculated power amount and color
	return formula, GetPowerColor(formula)
	
end

-- Power system (pkodev.mod.power)
-- Get color of power value 
function GetPowerColor(power)

	-- Green color (0xFF00FF00)
	return 4278255360
	
end