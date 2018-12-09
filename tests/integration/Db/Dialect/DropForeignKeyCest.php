<?php

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Test\Integration\Db\Dialect;

use IntegrationTester;

class DropForeignKeyCest
{
    /**
     * Tests Phalcon\Db\Dialect :: dropForeignKey()
     *
     * @param IntegrationTester $I
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function dbDialectDropForeignKey(IntegrationTester $I)
    {
        $I->wantToTest("Db\Dialect - dropForeignKey()");
        $I->skipTest("Need implementation");
    }
}