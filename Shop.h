#ifndef RPG_GAME_SHOP_H_
#define RPG_GAME_SHOP_H_

#include <vector>
#include "playerinventory.h"

class Shop {
public:
	using ItemStats = PlayerInventory::ItemStats;
	using ItemType = PlayerInventory::ItemType;

	Shop();

	const std::vector<ItemStats>& GetAvailableItems() const;
	int GetItemPrice(size_t index) const;

private:
	std::vector<ItemStats> available_items_;
	std::vector<int> item_prices_;
};

#endif