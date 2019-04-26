<?php
declare(strict_types=1);

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Test\Unit\Cache\Adapter\Memory;

use Phalcon\Cache\Adapter\Memory;
use UnitTester;

/**
 * Class GetKeysCest
 */
class GetKeysCest
{
    /**
     * Tests Phalcon\Cache\Adapter\Memory :: getKeys()
     *
     * @param UnitTester $I
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2019-04-13
     */
    public function storageAdapterMemoryGetKeys(UnitTester $I)
    {
        $I->wantToTest('Cache\Adapter\Memory - getKeys()');
        $adapter = new Memory();

        $adapter->clear();

        $key = 'key-1';
        $adapter->set($key, 'test');
        $actual = $adapter->has($key);
        $I->assertTrue($actual);

        $key = 'key-2';
        $adapter->set($key, 'test');
        $actual = $adapter->has($key);
        $I->assertTrue($actual);

        $expected = [
            'ph-memo-key-1',
            'ph-memo-key-2',
        ];
        $actual   = $adapter->getKeys();
        sort($actual);
        $I->assertEquals($expected, $actual);
    }
}