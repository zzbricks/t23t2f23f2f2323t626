#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <vector>
#include <memory>

#include "GDHistoryProvider.hpp"

namespace LHSettings {
	std::vector<std::shared_ptr<LevelProvider>> providers;
};

#include "ProviderPopup.hpp"

#include <Geode/modify/LevelSearchLayer.hpp>
class $modify(LHLevelSearchLayer, LevelSearchLayer) {
	bool init(int p0) {
		if (!LevelSearchLayer::init(p0)) {
			return false;
		}

		auto extrasearch = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("gj_folderBtn_001.png"),
			this,
			menu_selector(LHLevelSearchLayer::onMyButton)
		);

		auto menu = (CCMenu *)this->getChildByID("other-filter-menu");

#ifdef GEODE_IS_ANDROID
		extrasearch->setID("provider-button"_spr);

		auto children = menu->getChildren();

		auto last_child = (CCNode *)children->lastObject();
		auto pos = last_child->getPosition();
		auto csz = last_child->getContentSize();

		pos.y -= csz.width + 10.f;

		extrasearch->setPosition(pos);

		menu->addChild(extrasearch);
#else
		menu->addChild(extrasearch);
		menu->updateLayout();
#endif

		return true;
	}

	void onMyButton(CCObject*) {
		ProviderPopup *popup = ProviderPopup::create(LHSettings::providers);
	}
};

$execute {
	LHSettings::providers.push_back(std::make_shared<GDHistoryProvider>());
}
